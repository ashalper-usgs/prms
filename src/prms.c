/* United States Geological Survey (USGS)
 *
 * Precipitation Runoff Modeling System (PRMS)
 */

#define MAIN
#define MMF_C

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "defs.h"
#include "structs.h"
#include "globals.h"

#include "batch_run.h"
#include "batch_run_functions.h"
#include "build_lists.h"
#include "call_modules.h"
#include "control_addr.h"
#include "control_var.h"
#include "decldim.h"
#include "get_times.h"
#include "parse_args.h"
#include "print_model_info.h"
#include "print_params.h"
#include "print_vars.h"
#include "read_control.h"
#include "read_line.h"
#include "read_params.h"
#include "save_params.h"
#include "setup_cont.h"
#include "umalloc_etc.h"

/* in globals.c */
extern PARAM **unsort_params;
extern double Mdeltat;
extern long Mnsteps;
extern double Mdeltanext;

/* in parse_args.c */
extern char *MAltContFile;

/* in parse_args.c */
extern char *model_name;
extern char *executable_model;
extern int batch_run_mode;
extern int print_mode;
extern int run_period_of_record;
extern int runtime_graph_on;
extern int preprocess_on;

extern int call_modules(char *);
extern int call_setdims(void);

void alloc_space (void);

LIST *module_db;
MODULE_DATA *current_module;
FILE_DATA   **fd = NULL;
double Mprevjt = -1.0; /* the latest previous Julian time  */
char *Minpptr = NULL;  /* pointer to current position in data input line */
int  M_stop_run = 0;	      /* Run switch 0 -or 1 */
STAT_LIST_TYPE *Mfirst_stat_list = NULL; /* pointer to first entry
					    in stats link list */
long ParamBaseIsDirty = FALSE;
int max_dims;
int max_controls;

/*--------------------------------------------------------------------*\
  | FUNCTION     : main
  | COMMENT	 : Main function for PRMS.
  | PARAMETERS   :
  |     int argc -- Argument count of command line parameters.
  |     char *argv[] -- Command line parameters.
  | RETURN VALUE : int
\*--------------------------------------------------------------------*/
int main (int argc, char *argv[]) {
   int set_count;
   int i, j;
   char **set_name, **set_value;
   CONTROL *cp;
   char *cptr;
   double *dptr;
   float *fptr;
   long *lptr;
   char **cpt;
   struct stat stbuf;
   char	buf[512];
   char	*err;
   static int      num_param_files = 0;
   char   **fname;
   char pathname[FILENAME_MAX];
   int set_size;

   /*
   **  Maximum buffer size for reading lines from files.
   **  This used to be set as a C precompiler directive.
   **  That is still the default, but now users are give.
   **  the option to set this on the command line, otherwise
   **  size still comes from the defs.h file.
   */
   max_data_ln_len = MAXDATALNLEN;

   /*
   **  List of modules that are used by the model. This is
   **  determined by calls to declmodule
   */
   module_db = ALLOC_list ("Module Data Base", 0, 100);

   /*
   **	parse the command-line arguments
   */
   set_count = 0;
   set_size = 100;
   set_name = (char **)malloc (set_size * sizeof (char *));
   set_value = (char **)malloc (set_size * sizeof (char *));
   parse_args (argc, argv, &set_count, set_name, set_value, set_size);

   if (MAltContFile == NULL) {
     (void)fprintf (
	     stderr,
	     "Usage: Set the full path to the control file using "
	     "the '-C' option.\n\n"
	   );
     exit(0);
   }

   alloc_space ();

   setup_cont ();
   err = read_control (MAltContFile);
   if (err) {
     (void)fprintf (stderr,"%s\n", err);
     exit (1);           
   }

   fname =   control_svar ("param_file");
   num_param_files = control_var_size ("param_file");

   for (i = 0; i < set_count; i++) {
     cp = control_addr (*(set_name + i));
     if (cp) {

       (void)fprintf (stderr,"\nControl variable %s set to %s.\n\n",
		      *(set_name + i), *(set_value + i));

       cptr = (char *)strtok (*(set_value + i), ",");

       j = 0;
       while (cptr) {
	 if (cp->type == M_DOUBLE) {
	   dptr = (double *) cp->start_ptr;
	   dptr[j] = atof(cptr);
	 } else if (cp->type == M_FLOAT) {
	   fptr = (float *) cp->start_ptr;
	   fptr[j] = (float) atof(cptr);
	 } else if (cp->type == M_LONG) {
	   lptr = (long *) cp->start_ptr;
	   lptr[j] =  atol(cptr);
	 } else if (cp->type == M_STRING) {
	   cpt = (char **) cp->start_ptr;
	   cpt[j] = strdup (cptr);
	 }

	 cptr = (char *)strtok (NULL, ",");
	 j++;
       }

     } else {
       (void)fprintf (stderr,"\nControl variable %s not found -- ignored.\n\n",
		      *(set_name + i));
     }
   }

   fname =   control_svar ("param_file");
   num_param_files = control_var_size ("param_file");

   if (call_setdims()) {
     (void)fprintf(stderr, "\nERROR: Calling function 'call_setdims'\n");
     exit (1);
   }

   /*
   **	read dimension info from parameter file
   */
   if (stat (*control_svar("param_file"), &stbuf) != -1) {
     if (stbuf.st_size) {
     } else {
       (void)fprintf (stderr,buf, "Parameter File: %s is empty.",
		      *control_svar("param_file"));
       exit (1);
     }
   }
    
   err = read_dims (*control_svar("param_file"));
   if (err) {
     fprintf (stderr,"\n%s\n", err);
     exit (1);
   }

   fname = control_svar ("param_file");
   num_param_files = control_var_size ("param_file");

   if (call_modules("declare")) {
     (void)fprintf(
	     stderr,
	     "\nERROR: in declare procedure, in function 'call_modules'\n"
	   );
     exit (1);
   }
    
   /*
   **	read in parameter values from parameter file
   */
   fname =   control_svar ("param_file");
   num_param_files = control_var_size ("param_file");

   /*
   **  Look for, declare and read in mapping parameters before any of
   **  the "module" parameters.
   */
   for (i = 0; i < num_param_files; i++) {
     if (stat (fname[i], &stbuf) != -1) {
       if (stbuf.st_size) {
       } else {
	 (void)fprintf (stderr, buf, "ERROR: Parameter file: %s is empty.",
			fname[i]);
	 exit (1);
       }
     }
     
     err = read_params (fname[i], i, 1);
     if (err) {
       (void)fprintf (stderr,"\n%s\n", err);
       exit (1);
     }
   }

   /*
   **  Read in the parameters declared by the modules.
   */
   for (i = 0; i < num_param_files; i++) {
     if (stat (fname[i], &stbuf) != -1) {
       if (stbuf.st_size) {
       } else {
	 (void)fprintf (stderr,buf, "ERROR: Parameter file: %s is empty.",
			fname[i]);
	 exit (1);
       }
     }
	    
     err = read_params (fname[i], i, 0);
     if (err) {
       (void)fprintf (stderr,"\n%s\n", err);
       exit (1);
     }
   }
    
   /*
   **  get data info string into the global
   */
   err = READ_data_info ();
   if (err) (void)fprintf (stderr,"\nMMS - Warning: %s", err);

   /*
   **	get start and end time
   */
   get_times ();
    
   if (print_mode) {
     print_params();
     print_vars();
     print_model_info();
     (void)snprintf (pathname, FILENAME_MAX, "%s.param", MAltContFile);
     save_params (pathname);
   } else {
      BATCH_run ();
   }

   exit (0);
}

/* Global variables, referenced in MMS, C modules for legacy
   reasons. */

LIST *cont_db;
LIST *dim_db;
int max_vars;
PUBVAR **Mvarbase = NULL;   /* pointer to public variables database */
long Mnvars = 0;	    /* no of public variables in database */
int max_params;
PARAM **Mparambase = NULL;  /* pointer to parameter database */
long Mnparams = 0;	    /* no of params in database */
int max_read_vars;
READCHECK **Mcheckbase = NULL;	/* pointer to read check database */
long Mnreads = 0;	  /* max no. of calls to be made by readvar */
DATETIME *Mstrttime = NULL;	/* pointer to start time structure */
DATETIME *Mendtime = NULL;	/* pointer to end time structure */
DATETIME *Mnowtime = NULL; /* pointer to current data time structure */
DATETIME *Mnexttime = NULL;  /* pointer to next data time structure */
char *Mparaminfo = NULL;     /* pointer to param information string */
char *Mdatainfo = NULL;	     /* pointer to data information string */

void alloc_space (void) {
  static DATETIME start, end, now, next;

  cont_db = ALLOC_list ("Control Data Base", 0, 100);

  /*
   * space for the dimension pointer array
   */

  dim_db = ALLOC_list ("Dimension Data Base", 0, 50);

  /*
   * default dimension "one"
   */

  decldim ("one", 1, 1, "Dimension of scalar parameters and variables");

  /*
   * space for the public variable pointer array
   */

  max_vars = 500;
  Mvarbase = (PUBVAR **) umalloc (max_vars * sizeof(PUBVAR *));
  Mnvars = 0;

  /*
   * space for the parameter pointer array
   */

  max_params = 500;
  Mparambase = (PARAM **) umalloc (max_params * sizeof(PARAM *));
  Mnparams = 0;

  /*
   * space for the read check data base
   */

  max_read_vars = 50;
  Mcheckbase = (READCHECK **) umalloc (max_read_vars * sizeof(READCHECK *));
  Mnreads = 0;

  /*
   * space for time structures
   */
  Mstrttime = &start;
  Mendtime = &end;
  Mnowtime = &now;
  Mnexttime = &next;

  /*
   * space for run info. string
   */
  Mparaminfo = strdup ("Default case");
  Mdatainfo = strdup ("Default case");
}

/**
 * FUNCTION     : BATCH_run
 * PARAMETERS   : None
 * RETURN VALUE : int - error code if there is one.
 * RESTRICTIONS : None
 * COMMENT  : Runs the MMS time loop.
 */
int BATCH_run (void) {
  char *ret;
  long endofdata = 0;

  ret = single_run_pre_init ();
  if (ret) {
    fprintf (stderr,"%s\n", ret);
    return(1);
  }

  if (call_modules("initialize")) {
    fprintf (stderr, "single_run:  Problem with initializing modules.");
    return(1);
  }

  ret = single_run_post_init ();
  if (ret) return(1);

  /*
   * perform the main loop
   */

  M_stop_run = 0;
  Mprevjt = -1.0;

  while(!endofdata) {
    if(!(endofdata = read_line ())) {
      ret = single_run_pre_run ();
      if (ret) return(1);

      errno = 0;

      if(call_modules("run")) {
	fprintf (stderr, "Problem while running modules.");
	return(1);
      }

      ret = single_run_post_run ();
      if (ret) return(1);
    }
  }

  ret = single_run_post_cleanup ();
  if (ret) return(1);

  /*
   * cleanup modules
   */

  if (call_modules("cleanup")) {
    fprintf (stderr, "Problem with module cleanup.");
    return(1);
  }

  return(0);
}

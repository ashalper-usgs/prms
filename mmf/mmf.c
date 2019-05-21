/* United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : xmms
 * COMMENT  : main driver for xmms
 */

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "protos.h"

extern int call_modules(char *);
extern int call_setdims(void);

int max_data_ln_len;	/* now possible to set this on command line */
char *MAltContFile = NULL;	/* Alt. name of control file */
long Mdebuglevel = 0;		/* the current debug level */
char *model_name = NULL;
char *executable_model = NULL;
int batch_run_mode = FALSE;	/* flag for running in batch mode  */
int run_period_of_record = FALSE; /* flag for running entire period of
				     record in batch mode  */
int print_mode = FALSE;
int runtime_graph_on = FALSE;
int preprocess_on = FALSE;   /* flag for running in preprocess mode */
LIST *cont_db;
LIST *dim_db;
LIST *module_db;
MODULE_DATA *current_module;
PUBVAR **Mvarbase = NULL;  /* pointer to public variables data base */
long Mnvars = 0;	   /* no of public variables in data base */
PARAM **Mparambase = NULL; /* pointer to parameter data base */
long Mnparams = 0;	   /* no of params in data base */
READCHECK **Mcheckbase = NULL;	/* pointer to read check data base */
long Mnreads = 0;	   /* max no. of calls to be made by readvar */
DATETIME *Mstrttime = NULL;	/* pointer to start time structure */
DATETIME *Mendtime = NULL;	/* pointer to end time structure */
DATETIME *Mnowtime = NULL; /* pointer to current data time structure */
DATETIME *Mnexttime = NULL;  /* pointer to next data time structure */
char *Mparaminfo = NULL;     /* pointer to param information string */
char *Mdatainfo = NULL;	     /* pointer to data information string */
PARAM **unsort_params = NULL;	/* pointer to unsorted parameters */
FILE_DATA   **fd = NULL;
long Mnsteps = 0;      /* the number of steps so far */
double Mprevjt = -1.0; /* the latest previous Julian time  */
double Mdeltat = 0.0;  /* the latest time step in hours */
char *Minpptr = NULL;  /* pointer to current posn in data input line*/
double Mdeltanext = 0.0;      /* the latest next time step in hours */
int  M_stop_run = 0;	      /* Run switch 0 -or 1 */
STAT_LIST_TYPE *Mfirst_stat_list = NULL; /* pointer to first entry
					    in stats link list */
char *Mtypes[] = {"", "long", "float", "double", "string", "", "","", "", ""};
long ParamBaseIsDirty = FALSE;
int max_vars;
int max_params;
int max_read_vars;
int max_dims;
int max_controls;

/*--------------------------------------------------------------------*\
  | FUNCTION     : main
  | COMMENT	 : Main source for xmms
  | PARAMETERS   :
  |     int argc -- Argument count of command line parameters.
  |     char *argv[] -- Command line parameters.
  | RETURN VALUE : None
  | RESTRICTIONS : None
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
      (void)fprintf (stderr,"Usage: Set the full path to the control file using the '-C' option.\n\n");
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

	fname =   control_svar ("param_file");
    num_param_files = control_var_size ("param_file");

    if (call_modules("declare")) {
		(void)fprintf(stderr, "\nERROR: in declare procedure, in function 'call_modules'\n");
        exit (1);
	}
    
    /*
    **	read in parameter values from parameter file
    */
	fname =   control_svar ("param_file");
    num_param_files = control_var_size ("param_file");

	/*
	**  Look for, declare and read in mapping parameters before any of the "module" parameters
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
      ;
    }

    exit (0);
}

/* United States Geological Survey (USGS)
 *
 * Precipitation Runoff Modeling System (PRMS)
 */

#define MAIN
#define MMF_C

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "defs.h"
#include "structs.h"
#include "globals.h"

#include "build_lists.h"
#include "check_vars.h"
#include "control_addr.h"
#include "control_var.h"
#include "create_vstats.h"
#include "decldim.h"
#include "dim_addr.h"
#include "free_vstats.h"
#include "get_times.h"
#include "graph_single_run.h"
#include "julday.h"
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
#include "var_addr.h"
#include "write_vstats.h"

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

extern int call_setdims(void);

void alloc_space (void);
int BATCH_run (void);
int call_modules(char *);

char *single_run_pre_init (void);
char *single_run_post_init (void);
char *single_run_pre_run (void);
char *single_run_post_run (void);
char *single_run_post_cleanup (void);

LIST *module_db;
MODULE_DATA *current_module;
FILE_DATA   **fd = NULL;
double Mprevjt = -1.0; /* the latest previous Julian time  */
char *Minpptr = NULL;  /* pointer to current position in data input line */
int  M_stop_run = 0;   /* Run switch 0 -or 1 */
/* pointer to first entry in stats link list */
STAT_LIST_TYPE *Mfirst_stat_list = NULL;
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

/* doesn't appear to be called anywhere for reasons unknown */
char *single_run_pre_cleanup (void);

/* in parse_args.c */
extern int preprocess_on;

static FILE *statvar_file;
static FILE **ani_out_files;
static long nstatVars, naniVars;
static char **statVar_names, **statVar_element;
static char **aniVar_names;
static char statvar_path[FILENAME_MAX];
static char ani_path[FILENAME_MAX];
static char buf[256];
static long i, j, stats_flag, ani_out_flag;
static char *err_message, *c;
static char err[256];
static int started;
static PUBVAR **ani_out_vars, *var;
static DIMEN **ani_out_dims, *dim;
static DIMEN *nhrudim, *ngwdim, *nssrdim, *foobar;
static FILE **ani_var_files;
static int num_ani_dims, found, k;
static DATETIME start_of_data, end_of_data;

/*--------------------------------------------------------------------*\
  | FUNCTION     : single_run_pre_init
  | RETURN VALUE : char *
\*--------------------------------------------------------------------*/
char *single_run_pre_init (void) {

  stats_flag = *control_lvar ("statsON_OFF");
  if (stats_flag == 1)
    nstatVars = *control_lvar("nstatVars");
  else
    nstatVars = 0;

  if (!nstatVars)
    stats_flag = 0;

  ani_out_flag = *control_lvar ("aniOutON_OFF");
  if (ani_out_flag == 1)
    naniVars = *control_lvar("naniOutVars");
  else
    naniVars = 0;

  if (!naniVars)
    ani_out_flag = 0;

  /*
  **  Make sure that all of the selected stat and display variables are OK
  **  before a run is attempted.
  */
  if (stats_flag) {
    err_message = CHECK_stat_vars();
    if (err_message) return (err_message);
  }

  if (ani_out_flag) {
    err_message = CHECK_ani_vars ();
    if (err_message) return (err_message);
  }

  /*
   * create stats vars linked list
   */
  if (stats_flag)
    create_vstats();

  /*
   * open data file
   * ensure datainfo is up to date
   */
  err_message = DATA_read_init ();
  if (err_message) {
    (void)printf ("%s\n", err_message);
    return (err_message);
  }

  /*
   * **  Reset run period to period of record if -por flag set
   */
  if (run_period_of_record) {
    DATA_find_end (&start_of_data, &end_of_data);
    julday (&start_of_data);
    julday (&end_of_data);

    printf (
     "resetting model start time to period of record %ld %ld %ld %ld %ld %ld\n",
     start_of_data.year, start_of_data.month, start_of_data.day,
     start_of_data.hour, start_of_data.min, start_of_data.sec
    );

    printf (
      "resetting model end time to period of record %ld %ld %ld %ld %ld %ld\n",
      end_of_data.year, end_of_data.month, end_of_data.day,
      end_of_data.hour, end_of_data.min, end_of_data.sec
    );

    Mendtime = &end_of_data;
    Mstrttime = &start_of_data;
  }

  err_message = DATA_check_start ();
  if (err_message) {
    (void)printf ("%s\n", err_message);
    return (err_message);
  }

  /*
   * Open statvar file, and store number of variables and variable names
   */
  if (stats_flag) {
    (void)snprintf(statvar_path, FILENAME_MAX, "%s",
		   *((char **) control_var("stat_var_file")));

    if ((statvar_file = fopen(statvar_path, "w")) == NULL) {
      (void)snprintf (err, 256,
		      "ERROR - single_run: Could not open statvar file '%s'\n",
		      statvar_path);
      return (err);
    }

    statVar_names = (char **) control_var("statVar_names");
    statVar_element = (char **) control_var("statVar_element");

    /*
     * write number of variables and statVars names to stats data file.
     */
    (void)fprintf(statvar_file,"%ld\n",nstatVars);

    for (i = 0; i < nstatVars; i++)
      (void)fprintf(statvar_file,"%s %s\n",
		    statVar_names[i], statVar_element[i]);
  }

  /*
   * Open ani output files.
   */
  if (ani_out_flag) {
    aniVar_names = (char **) control_var("aniOutVar_names");
    (void)snprintf(ani_path, FILENAME_MAX, "%s",
		   *((char **) control_var("ani_output_file")));

    ani_out_dims = (DIMEN **)malloc (naniVars * sizeof (DIMEN *));
    ani_var_files = (FILE **)malloc (naniVars * sizeof (FILE *));
    ani_out_vars = (PUBVAR **)malloc (naniVars * sizeof (PUBVAR *));

    /*
    **  Get the pubvars.
    */
    for (i = 0; i < naniVars; i++) {

      c = strchr (aniVar_names[i], '.');
      if (c)
	*c = '\0';

      snprintf (buf, 256, "%s.%s", ani_path, aniVar_names[i]);
      c = strchr (buf, ' ');
      if (c)
	*c = '\0';

      ani_out_vars[i] = var_addr (aniVar_names[i]);
    }

    /*
    **  List of unique ANIMATION dimensions.
    */
    num_ani_dims = 0;
    nhrudim = dim_addr("nhru");
    ngwdim = dim_addr("ngw");
    nssrdim = dim_addr("nssr");
    for (i = 0; i < naniVars; i++) {
      found = FALSE;
       
      /* Reset ngw and nssr dimensions to nhru for the purposes of the
	 animation file.*/
      foobar = ani_out_vars[i]->dimen[0];
      if (foobar == ngwdim || foobar == nssrdim) {
	foobar = nhrudim;
      }

      for (j = 0; j < num_ani_dims; j++) {
	if (foobar == ani_out_dims[j]) {
	  found = TRUE;
	}
      }

      if (!found) {
	ani_out_dims[j] = foobar;
	num_ani_dims++;
      }
    }

    /*
    **  Open a file for each dimension.
    */
    ani_out_files = (FILE **)malloc (num_ani_dims * sizeof (FILE *));

    for (i = 0; i < num_ani_dims; i++) {
      snprintf (buf, 256, "%s.%s", ani_path, ani_out_dims[i]->name);
      if ((ani_out_files[i] = fopen(buf, "w")) == NULL) {
	(void)snprintf (err, 256,
			"ERROR - single_run: Could not open ani file '%s'\n",
			buf);
	return (err);
      }

      fprintf (ani_out_files[i], "#\n# Begin DBF\n");
      fprintf (ani_out_files[i], "# timestamp,#FIELD_ISODATE,10,0\n");
      fprintf (ani_out_files[i], "# %s,#FIELD_DECIMAL,10,2\n",
	       ani_out_dims[i]->name);
    }

    /*
    **  Map each variable to a file.
    */
    for (i = 0; i < naniVars; i++) {
      /* Reset ngw and nssr dimensions to nhru for the purposes of the
	 animation file.*/
      foobar = ani_out_vars[i]->dimen[0];
      if (foobar == ngwdim || foobar == nssrdim) {
	foobar = nhrudim;
      }

      for (j = 0; j < num_ani_dims; j++) {
	if (foobar == ani_out_dims[j]) {
	  ani_var_files[i] = ani_out_files[j];
	}
      }
    }

    /*
    **  Finish writing the headers.
    */
    for (i = 0; i < naniVars; i++)
      fprintf (ani_var_files[i], "# %s,#FIELD_DECIMAL,10,2\n",
	       ani_out_vars[i]->name);

    for (i = 0; i < num_ani_dims; i++) {
      fprintf (ani_out_files[i], "# End DBF\n#\n");
    }

    /*
    **  Write variable name line
    */
    for (i = 0; i < num_ani_dims; i++) {
      fprintf (ani_out_files[i], "timestamp	%s", ani_out_dims[i]->name);
    }

    for (i = 0; i < naniVars; i++) {
      fprintf (ani_var_files[i], "	%s", ani_out_vars[i]->name);
    }

    for (i = 0; i < num_ani_dims; i++)
      fprintf (ani_out_files[i], "\n");

    /*
    **  Write variable size line
    */
    for (i = 0; i < num_ani_dims; i++) {
      fprintf (ani_out_files[i], "10d	10n");
    }

    for (i = 0; i < naniVars; i++) {
      fprintf (ani_var_files[i], "	10n");
    }

    for (i = 0; i < num_ani_dims; i++)
      fprintf (ani_out_files[i], "\n");

  }

  /*
  **  set initial values of nsteps global variable if they
  **  don't come from the var init file
  */
  Mnsteps = 0;

  /*
   * initialize modules
   */

  errno = 0;
  return(NULL);
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : single_run_post_init
  | RETURN VALUE : char *
\*--------------------------------------------------------------------*/
char *single_run_post_init (void) {

  initializeRuntimeGraphs();

  /*
  **  set initial values of nsteps global variable if they
  **  don't come from the var init file
  */
  Mnsteps = 0;

  started = FALSE;

  return (NULL);
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : single_run_pre_run
  | RETURN VALUE : char *
\*--------------------------------------------------------------------*/
char *single_run_pre_run (void) {

  started = TRUE;

  errno = 0;
  return (NULL);
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : single_run_post_run
  | RETURN VALUE : char *
\*--------------------------------------------------------------------*/
char *single_run_post_run (void) {

  if (stats_flag)
    write_vstats (statvar_file);

  /*
  **  Write the ANIMATION output variables to their respective files.
  */
  if (ani_out_flag) {

    /*
    **  Each dimension has it's own file.
    */
    for (i = 0; i < num_ani_dims; i++) {
      dim = ani_out_dims[i];
      for (j = 0; j < dim->value; j++) {

	/*
	**  Write the current time stamp to the dimension file.
	*/
	fprintf (ani_out_files[i], "%4ld-%02ld-%02ld %10ld",
		 Mnowtime->year,
		 Mnowtime->month, Mnowtime->day, j + 1);

	/*
	**  Write the variable values to the dimension file.
	*/
	for (k = 0; k < naniVars; k++) {
	  var = ani_out_vars[k];
	  switch (var->type) {
	  case M_DOUBLE:
	    fprintf (ani_var_files[k], " %10.3e",
		     *((double *) var->value + j));
	    break;

	  case M_FLOAT:
	    fprintf (ani_var_files[k], " %10.3e",
		     *((float *) var->value + j));
	    break;

	  case M_LONG:
	    fprintf (ani_var_files[i], "\t%10d",
		     *((int *) var->value + j));
	    break;
	  }
	}
	fprintf (ani_out_files[i], "\n");
      }
    }
  }

  plotRuntimeGraphValue();

  return (NULL);
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : single_run_pre_cleanup
  | RETURN VALUE : char *
\*--------------------------------------------------------------------*/
char *single_run_pre_cleanup (void) {
  return (NULL);
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : single_run_post_cleanup
  | RETURN VALUE : char *
\*--------------------------------------------------------------------*/
char *single_run_post_cleanup (void) {

  /*
   * free up stats vars linked list
   */
  if (stats_flag)
    free_vstats();

  /*
   * close files and tidy up
   */
  DATA_close ();

  if (stats_flag)
    fclose(statvar_file);

  /*
  **  Close the ANIMATION output files
  */
  if (ani_out_flag) {
    for (i = 0; i < num_ani_dims; i++)
      fclose (ani_out_files[i]);

  }

  closeRuntimeGraphs();

  if (!started) {
    return ("Run period outside of data in file.");
  }

  /*
   * if required, save vars to file
   */
  if (preprocess_on) {
    write_preprocess_params ();
  }

  return (NULL);
}

extern long call_modules_ (char *, ftnlen);

int call_modules(char *arg) {
  long retval;
  ftnlen len;

  len = (ftnlen)strlen(arg);
  retval = call_modules_ (arg, len);
  return((int)retval);
}

/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : print_vars
 * COMMENT  : prints the var database to a file
 */

#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "globals.h"
#include "defs.h"
#include "control_var.h"
#include "umalloc_etc.h"
#include "print_vars.h"

extern char *Mtypes[];		/* in globals.c */

/* in prms.c */
extern PUBVAR **Mvarbase;
extern long Mnvars;
extern DATETIME *Mstrttime;
extern DATETIME *Mendtime;
extern DATETIME *Mnowtime;

/* in parse_args.c */
extern char *MAltContFile;

/*--------------------------------------------------------------------*\
 | FUNCTION     : print_vars
\*--------------------------------------------------------------------*/
int print_vars (long Mnsteps) {

  char pathname[FILENAME_MAX], *infostr;
  FILE *var_file;
  PUBVAR *var;
  long i, j;

  /*
   * get var file path name, open file
   */

  (void)snprintf (pathname, FILENAME_MAX, "%s.var_name", MAltContFile);


  if ((var_file = fopen (pathname, "w")) == NULL) {
    (void)fprintf(stderr,
	    "ERROR - print_vars - creating file '%s'\n", pathname);
    perror("");

    return(1);
  }

  /*
   * write header
   */

  (void)fprintf(var_file, "PRMS\n");
  (void)fprintf(var_file, "============\n\n");

  (void)fprintf(var_file, "Description of variables required in the application.\n\n");

  /*
   * write file names
   */

  (void)fprintf(var_file, "Parameter file: %s\n", *control_svar("param_file"));
  (void)fprintf(var_file, "Data file     : %s\n", *control_svar("data_file"));
  (void)fprintf(var_file, "\n");

  /*
   * write the run info string
   */

  infostr = (char *) umalloc (strlen(Mparaminfo) + 1);
  (void)strncpy(infostr, Mparaminfo, strlen(Mparaminfo) + 1);
  (void)fprintf(var_file, "%s\n\n", infostr);

  /*
   * write start and end times, and step number
   */

  (void)fprintf(var_file, "Start time        : %02ld:%02ld:%02ld  %02ld/%02ld/%04ld\n",
	  Mstrttime->hour, Mstrttime->min, Mstrttime->sec,
	  Mstrttime->month, Mstrttime->day, Mstrttime->year);
  (void)fprintf(var_file, "End time          : %02ld:%02ld:%02ld  %02ld/%02ld/%04ld\n",
	  Mendtime->hour, Mendtime->min, Mendtime->sec,
	  Mendtime->month, Mendtime->day, Mendtime->year);
  (void)fprintf(var_file, "Current time      : %02ld:%02ld:%02ld  %02ld/%02ld/%04ld\n",
	  Mnowtime->hour, Mnowtime->min, Mnowtime->sec,
	  Mnowtime->month, Mnowtime->day, Mnowtime->year);
  (void)fprintf(var_file, "Current time step : %8ld\n", Mnsteps);

  /*
   * write out variable values
   */

  for (i = 0; i < Mnvars; i++) {

    var = Mvarbase[i];

    if (!(var->private)) {

       (void)fprintf(var_file, "\n");
       (void)fprintf(var_file, "Name: %s\n", var->name);
       (void)fprintf(var_file, "Module: %s\n", var->module);
       (void)fprintf(var_file, "Ndimen: %ld\n", var->ndimen);
       (void)fprintf(var_file, "Dimensions: ");

       for (j = 0; j < var->ndimen; j++) {
         (void)fprintf(var_file, "%s - %ld",
	         var->dimen[j]->name, var->dimen[j]->value);
         if (j < var->ndimen - 1)
	   (void)fprintf(var_file, ", ");
       } /* j */

       (void)fprintf(var_file, "\n");
       (void)fprintf(var_file, "Size: %ld\n", var->size);
       (void)fprintf(var_file, "Type: %s\n", Mtypes[var->type]);
/* DANGER */
       (void)fprintf(var_file, "Desc: %s\n", var->help);
/* DANGER */
       (void)fprintf(var_file, "Units: %s\n", var->units);
       if (var->private)
          (void)fprintf(var_file, "Private \n");
     }
    
  } /* i */

  fclose(var_file);
  
  return(0);

}

/*--------------------------------------------------------------------*\
 | FUNCTION     : print_var
\*--------------------------------------------------------------------*/
void print_var (FILE *var_file, PUBVAR *var, long l, long nl, long k, long nk,
	long j) {
  
  long ind;

  switch (var->ndimen) {

  case 1:

    ind = l;
    break;

  case 2:

    ind = l + k * nl;
    break;

  default:

    ind = l + k * nl + j * nl * nk;
    break;

  } /* switch (var->ndimen) */

  switch (var->type) {

  case M_DOUBLE:
    (void)fprintf(var_file, " %10lg", *((double *) var->value + ind));
    break;
	
  case M_FLOAT:
    (void)fprintf(var_file, " %10g", *((float *) var->value + ind));
    break;
	
  case M_LONG:
    (void)fprintf(var_file, " %10ld", *((long *) var->value + ind));
    break;
	
  } /* switch (var->type) */

}

/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : print_params
 * COMMENT  : prints the param data base to a file
 */

#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "globals.h"
#include "defs.h"
#include "control_var.h"
#include "umalloc_etc.h"
#include "print_params.h"

extern char *Mtypes[];		/* in globals.c */

/* in alloc_space.c */
extern LIST *dim_db;
extern PARAM **Mparambase;
extern long Mnparams;
extern char *Mparaminfo;

/* in parse_args.c */
extern char *MAltContFile;

/*--------------------------------------------------------------------*\
 | FUNCTION     : print_params
\*--------------------------------------------------------------------*/
int print_params (void) {

  char pathname[FILENAME_MAX], *infostr;
  FILE *param_file;
  PARAM *param;
  DIMEN *dim;
  long i, j;

  /*
   * get param file path name, open file
   */

  (void)snprintf (pathname, FILENAME_MAX, "%s.par_name", MAltContFile);

  if ((param_file = fopen (pathname, "w")) == NULL) {
    (void)fprintf(stderr,
		"ERROR: creating Parameter Name File: '%s'\n", pathname);
    perror("");
    return(1);
  }

  /*
   * write header
   */

  (void)fprintf(param_file, "PRMS\n");
  (void)fprintf(param_file, "============\n\n");

  (void)fprintf(param_file, "Description of dimensions and parameters required in the application.\n\n");

  /*
   * write file name
   */

  (void)fprintf(param_file, "Parameter file: %s\n", *control_svar("param_file"));
  (void)fprintf(param_file, "\n");

  /*
   * write the run info string
   */

  infostr = (char *) umalloc (strlen(Mparaminfo) + 1);
  (void)strncpy(infostr, Mparaminfo, strlen(Mparaminfo) + 1);
  (void)fprintf(param_file, "%s\n\n", infostr);

  /*
   * write out dimensions
   */

  (void)fprintf(param_file, "--------------- DIMENSIONS ---------------\n");

	for (i = 0; i < dim_db->count; i++) {
		dim = (DIMEN *)(dim_db->itm[i]);
			(void)fprintf(param_file, "\n");
			(void)fprintf(param_file, "Name  : %s\n", dim->name);
			(void)fprintf(param_file, "Value : %ld\n", dim->value);
			(void)fprintf(param_file, "Desc  : %s\n", dim->descr);
			if (dim->fixed) {
			   (void)fprintf(param_file, "Fixed\n");
			}
	}

  /*
   * write out parameter values etc
   */

  (void)fprintf(param_file, "\n--------------- PARAMETERS ---------------\n");

  for (i = 0; i < Mnparams; i++) {

    param = Mparambase[i];
	if (param->max != NULL){


		(void)fprintf(param_file, "\n");
		(void)fprintf(param_file, "Name      : %s\n", param->name);
		(void)fprintf(param_file, "Module    : %s\n", param->module);
		(void)fprintf(param_file, "Descr     : %s\n", param->descr);
		(void)fprintf(param_file, "Help      : %s\n", param->help);
		(void)fprintf(param_file, "Ndimen    : %ld\n", param->ndimen);
		(void)fprintf(param_file, "Dimensions: ");

		for (j = 0; j < param->ndimen; j++) {
			(void)fprintf(param_file, "%s - %ld",
				param->dimen[j]->name, param->dimen[j]->value);
			if (j < param->ndimen - 1)
				(void)fprintf(param_file, ", ");
		} /* j */

		(void)fprintf(param_file, "\n");
		(void)fprintf(param_file, "Size      : %ld\n", param->size);
		(void)fprintf(param_file, "Type      : %s\n", Mtypes[param->type]);
		(void)fprintf(param_file, "Units     : %s\n", param->units);
		if (param->format)
			(void)fprintf(param_file, "Format    : %s\n", param->format);
		(void)fprintf(param_file, "Width     : %ld\n", param->column_width);

		switch (param->type) {
		case M_LONG:
			/* DANGER
		   (void)fprintf (param_file, "Max       : %ld\n", *(long *)(param->max));
		   (void)fprintf (param_file, "Min       : %ld\n", *(long *)(param->min));
		   (void)fprintf (param_file, "Default   : %ld\n", *(long *)(param->def));
		   */
			(void)fprintf(param_file, "Max       : %d\n", *(int *)(param->max));
			(void)fprintf(param_file, "Min       : %d\n", *(int *)(param->min));
			(void)fprintf(param_file, "Default   : %d\n", *(int *)(param->def));
			break;

		case M_FLOAT:
			(void)fprintf(param_file, "Max       : %f\n", *(float *)(param->max));
			(void)fprintf(param_file, "Min       : %f\n", *(float *)(param->min));
			(void)fprintf(param_file, "Default   : %f\n", *(float *)(param->def));
			break;

		case M_DOUBLE:
			(void)fprintf(param_file, "Max       : %lf\n", *(double *)(param->max));
			(void)fprintf(param_file, "Min       : %lf\n", *(double *)(param->min));
			(void)fprintf(param_file, "Default   : %lf\n", *(double *)(param->def));
			break;

        // 2016-01-13 PAN: added case for writing out min/max/default values for string parameters
        case M_STRING:
			(void)fprintf(param_file, "Max       : %s\n", *(char **)(param->max));
			(void)fprintf(param_file, "Min       : %s\n", *(char **)(param->min));
			(void)fprintf(param_file, "Default   : %s\n", *(char **)(param->def));
            break;
		}

		if (param->bound_status == M_BOUNDED) {
			(void)fprintf(param_file, "Bounded   : %s\n", (param->bound_dimen)->name);
		}

	}
  } /* i */

  fclose(param_file);

  return(0);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : print_param
\*--------------------------------------------------------------------*/
void print_param (FILE *param_file, PARAM *param, long l, long nl, long k,
	long nk, long j) {
  long ind;

  switch (param->ndimen) {

  case 1:

    ind = l;
    break;

  case 2:

    ind = l + k * nl;
    break;

  default:

    ind = l + k * nl + j * nl * nk;
    break;

  } /* switch (param->ndimen) */

  switch (param->type) {

  case M_DOUBLE:
    (void)fprintf(param_file, " %10lg", *((double *) param->value + ind));
    break;

  case M_FLOAT:
    (void)fprintf(param_file, " %10g", *((float *) param->value + ind));
    break;

  case M_LONG:
    (void)fprintf(param_file, " %10ld", *((long *) param->value + ind));
    break;

  } /* switch (param->type) */
}

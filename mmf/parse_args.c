/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : parse_args
 * COMMENT  : parses the command line arguments
 */

#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "globals.h"
#include "defs.h"
#include "parse_args.h"

long Mdebuglevel = 0;		/* the current debug level */
char *MAltContFile = NULL;	/* Alt. name of control file */
char *model_name = NULL;
char *executable_model = NULL;
int batch_run_mode = FALSE;	/* flag for running in batch mode  */
int print_mode = FALSE;
int run_period_of_record = FALSE; /* flag for running entire period of
				     record in batch mode  */
int runtime_graph_on = FALSE;
int preprocess_on = FALSE;   /* flag for running in preprocess mode */
int max_data_ln_len;	/* now possible to set this on command line */

/*--------------------------------------------------------------------*\
 | FUNCTION     : parse_args
 | RETURN VALUE : None.
\*--------------------------------------------------------------------*/
void parse_args (int argc, char **argv, int *set_count, char **set_name, char **set_value, int set_size) {

   int i;
   char *ptr;

   Mdebuglevel = 0;
   MAltContFile = strdup ("control");

/*
**  Get the model name.
*/
   ptr = strrchr (argv[0], '/');
   if (!ptr) ptr = strrchr (argv[0], '\\');
   if (ptr) ++ptr;
   else ptr = argv[0];

   model_name = strdup (ptr);

   executable_model = strdup (argv[0]);
   ptr = strstr (executable_model, ".exe");
   if (ptr) *ptr = '\0';

   if (argc >= 2) {
      for (i = 1; i < argc ; i++) {
		 if (!strcmp(argv[i], "-debug")) {
			 Mdebuglevel = atoi(argv[i+1]);
			 i++;

		 } else if (!strncmp(argv[i],"-C",2)) {
            MAltContFile = (char *)((argv[i]));
            MAltContFile+=2;

         } else if (!strncmp(argv[i],"-batch", 6)){
            batch_run_mode = TRUE;

         } else if (!strncmp(argv[i],"-print", 6)){
            print_mode = TRUE;

         } else if (!strncmp(argv[i],"-por", 4)){
            run_period_of_record = TRUE;

         } else if (!strncmp(argv[i],"-rtg", 4)){
            runtime_graph_on = TRUE;

		 } else if (!strncmp(argv[i],"-preprocess", 11)){
            preprocess_on = TRUE;

         } else if (!strncmp(argv[i],"-set",4)){

            if ((*set_count) >= set_size) {
               printf("parse_args: Overflow. Too many command line arguements set with -set flag.\n\n\n");
               exit(1);
            }

            i++;
            *(set_name + *set_count) = strdup ((char *)((argv[i])));
            i++;
            *(set_value + *set_count) = strdup ((char *)((argv[i])));
            (*set_count)++;

		} else if (!strncmp(argv[i],"-MAXDATALNLEN",13)){
            max_data_ln_len = atoi(argv[i+1]);
			i++;

		 } else { // Assume argument with no flag is control file name
			MAltContFile = (char *)((argv[i]));
		 }
      }
   }
}

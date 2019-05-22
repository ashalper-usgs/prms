/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : print_model_info
 */

#include <stdio.h>
#include "structs.h"
#include "globals.h"

/* in parse_args.c */
extern char *MAltContFile;

#define PRINTLEN 77

/*--------------------------------------------------------------------*\
 | FUNCTION     : print_model_info
\*--------------------------------------------------------------------*/
int print_model_info (void) {

  char pathname[FILENAME_MAX];
  FILE *model_info_file;
  int i, j;
  MODULE_DATA *module;
  LIST *vlist, *plist;

	(void)snprintf (pathname, FILENAME_MAX, "%s.mod_name", MAltContFile);

	if ((model_info_file = fopen (pathname, "w")) == NULL) {
		(void)fprintf(stderr, "ERROR - print_model_info - creating file '%s'\n", pathname);
		perror("");
		return(1);
	}

  /*
   * write header
   */

	(void)fprintf(model_info_file, "PRMS Module Name File\n");
	(void)fprintf(model_info_file, "%s\n", model_name);
	(void)fprintf(model_info_file, "============\n\n");

	(void)fprintf(model_info_file, "Module versions used in the application, listed in computation order.\n\n");

	for (i = 0; i < module_db->count; i++) {
		// print module name
		module = (MODULE_DATA *)(module_db->itm[i]);
		fprintf(model_info_file, "%s,%s\n", module->name, module->version);

		// print the variables
		vlist = module->vars;
		fprintf(model_info_file, "   ");
		for (j = 0; j < vlist->count; j++) {
			fprintf(model_info_file, "%s,", (char *)(vlist->itm[j]));
		}
		fprintf(model_info_file, "\n");

		// print the parameters
		plist = module->params;
		fprintf(model_info_file, "   ");
		for (j = 0; j < plist->count; j++) {
			fprintf(model_info_file, "%s,", (char *)(plist->itm[j]));
		}
		fprintf(model_info_file, "\n");

	}
	//fprintf(model_info_file, "\n\n\n\n\n\n");

  fclose(model_info_file);

  return(0);
}

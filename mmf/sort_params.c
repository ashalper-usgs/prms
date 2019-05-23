/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : sort_params
 * COMMENT  : sorts the param array so that the key for each structure
 *            is in increasing alphabetical order
 */

#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "globals.h"

extern PARAM **unsort_params;	/* in globals.c */
extern long Mnparams;		/* in alloc_space.c */

/*--------------------------------------------------------------------*\
 | FUNCTION     : sort_params
\*--------------------------------------------------------------------*/
void sort_params (void) {

  PARAM **params;
  PARAM *tmpparam;
  int i, j;

  params =  Mparambase;

  /*
  **	Make a array of the unsorted parameter order.
  */
  if (!unsort_params) {
    unsort_params = (PARAM **)malloc (Mnparams * sizeof (PARAM *));
    for (i = 0; i < Mnparams; i++)
      unsort_params[i] = params[i];
  }

  /*
  **	Sort the parameter data base
  */
  for (i = Mnparams-2; i >= 0; i--) {
    for (j =  0; j <= i; j++) {
      if(strcmp(params[j]->key,params[j+1]->key) > 0) {
	tmpparam = params[j];
	params[j] = params[j+1];
	params[j+1] = tmpparam;
      }
    }
  }
}

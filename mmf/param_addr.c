/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : param_addr
 *            Returns a pointer to a PARAM struct which contains the given key;
 *            Returns NULL if key not found.
 */

#include "structs.h"
#include "globals.h"

/*--------------------------------------------------------------------*\
 | FUNCTION     : param_addr
\*--------------------------------------------------------------------*/
PARAM * param_addr (char *key) { 
  PARAM **params;
  long i;

  if (Mnparams == 0) return NULL; /* no parameters to locate */

  /*
   * get params from Mparambase, the global pointer
   */

  params = Mparambase;

  /*
   * search between 0 and Mnparams-1
   */

  for (i = 0; i < Mnparams; i++) {
    if (!strcmp(params[i]->key, key))
      return params[i];
  }

  /* if no match found, return null */
  return NULL;
}

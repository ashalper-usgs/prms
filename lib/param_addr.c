/*+
 * United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : param_addr
 *            returns a pointer to a PARAM struct which contains the given key
 *            returns NULL if key not found
 * COMMENT  :
 *
 * $Id$
 *
-*/

#define PARAM_ADDR_C

/**1************************ INCLUDE FILES ****************************/

#include <string.h>
#include "defs.h"
#include "structs.h"
#include "globals.h"
#include "protos.h"

/*--------------------------------------------------------------------*\
 | FUNCTION     : param_addr
 | COMMENT		:
 | PARAMETERS   :
 | RETURN VALUE : 
 | RESTRICTIONS :
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

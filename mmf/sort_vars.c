/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : sort_vars
 * COMMENT  : sorts the pubvar array so that the key for each
 *            structure is in increasing alphabetical order
 */

#include <string.h>
#include "structs.h"
#include "globals.h"

/*--------------------------------------------------------------------*\
 | FUNCTION     : sort_vars
\*--------------------------------------------------------------------*/
void sort_vars (void) {

  PUBVAR **vars;
  PUBVAR *tmpvar;
  int i, j;


  /*
   * get vars from varbase, the global pointer
   */

  vars =  Mvarbase;

  for (i = Mnvars-2; i >= 0; i--) {

    for (j =  0; j <= i; j++) {

      if(strcmp(vars[j]->key,vars[j+1]->key) > 0) {

	tmpvar = vars[j];
	vars[j] = vars[j+1];
	vars[j+1] = tmpvar;

      }

    }

  }
}


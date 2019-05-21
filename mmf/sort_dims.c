/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : sort_dims
 * COMMENT  : sorts the dimen array so that the key for each
 *            structure is in increasing alphabetical order
 */

#include <string.h>
#include "structs.h"
#include "globals.h"

/*--------------------------------------------------------------------*\
 | FUNCTION     : sort_dims
\*--------------------------------------------------------------------*/
void sort_dims (void) {
  int		i, j;
  DIMEN	*tmpdim, **dims;

  dims = (DIMEN **)(dim_db->itm);

  for (i = dim_db->count - 2; i >= 0; i--) {
    for (j =  0; j <= i; j++) {
      if (strcmp (dims[j]->name, dims[j+1]->name) > 0) {
	tmpdim = dims[j];
	dims[j] = dims[j+1];
	dims[j+1] = tmpdim;
      }
    }
  }
}

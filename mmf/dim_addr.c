/*+
 * United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : dim_addr
 *            returns a pointer to a DIMEN struct which contains the given name
 *            returns NULL if name not found
 * COMMENT  :
-*/

#define DIM_ADDR_C
#include <stdio.h>
#include <string.h>
#include "mms.h"
#include "dim_addr.h"

DIMEN *dim_addr (LIST *dim_db, char *name) { 
  long i;

  if (!dim_db->count)
    return (NULL);

  for (i = 0; i < dim_db->count; i++)
    if (!strcmp (((DIMEN *)(dim_db->itm[i]))->name, name))
      return ((DIMEN *)(dim_db->itm[i]));

  return (NULL);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : dim_notes
\*--------------------------------------------------------------------*/
char *dim_notes (LIST *dim_db, char *ch_ptr) {
  int		i, j;
  DIMEN	*dim;

  for (i = 0; i < dim_db->count; i++) {
    dim = (DIMEN *)(dim_db->itm[i]);
    for (j = 0; j < dim->value; j++)
      if (dim->names && dim->names[j] && (!strcmp (dim->names[j],ch_ptr)))
	return (dim->notes[j]);
  }

  return (NULL);
}


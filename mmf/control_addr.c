/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : control_addr
 * COMMENT  : Returns a pointer to a CONTROL struct which contains the
 *            given key; returns NULL if key not found.
 */

#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "globals.h"

extern LIST *cont_db;		/* in alloc_space.c */

CONTROL *control_addr (char *key) { 
  CONTROL *cp;
  int i;

  for (i = 0; i < cont_db->count; i++) {
    cp = (CONTROL *)(cont_db->itm[i]);
    if (!strcmp (cp->key, key))
      return (cp);
  }

  return (NULL);
}

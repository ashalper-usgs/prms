/*+
 * United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : control_addr
 * returns a pointer to a CONTROL struct which contains the given key
 * returns NULL if key not found
 * COMMENT  :
-*/

#define CONTROL_ADDR_C
#include <stdio.h>
#include <string.h>
#include "mms.h"
#include "control_addr.h"

CONTROL *control_addr (LIST *cont_db, char *key) { 
  CONTROL	*cp;
  int		i;

  for (i = 0; i < cont_db->count; i++) {
    cp = (CONTROL *)(cont_db->itm[i]);

    if (!strcmp (cp->key, key))
      return (cp);
  }

  return (NULL);
}

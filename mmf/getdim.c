/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : getdim() to be called from C
 *            getdim_() to be called from Fortran
 *            returns it as a long int. Returns -1 if error.
 * COMMENT  : gets the dimension associated with a name, and
 */

#include <string.h>
#include "defs.h"
#include "structs.h"
#include "protos.h"

/*--------------------------------------------------------------------*\
 | FUNCTION     : getdim_
 | COMMENT	: called from Fortran, sorts out args and calls getdim()
\*--------------------------------------------------------------------*/
long getdim_ (char *dname, ftnlen namelen) {
  char *name;
  long retval;

  /*
   * copy name and terminate
   */

  name = (char *) umalloc(namelen + 1);
  strncpy(name, dname, namelen);
  name[namelen] = '\0';

  /*
   * call C version of getdim()
   */

  retval =  getdim(name);

  return retval;
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : getdim
 | COMMENT	: is called from C
\*--------------------------------------------------------------------*/
long getdim (char *name) {

  DIMEN *dim;

  /*
   * get pointer to dimension with name
   */

  dim = dim_addr(name);

  if (dim == NULL) {
    (void)fprintf(stderr, 
	    "ERROR - getdim - dimension not found.\n");
    (void)fprintf(stderr, "Name:   '%s'\n", name);
    return(-1L);
  }

  /*
   * return the dimension
   */

  dim->got = TRUE;
  return dim->value;
}

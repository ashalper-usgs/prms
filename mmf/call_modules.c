/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : call_modules
 * COMMENT  : used to call a Fortran version
 */

#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "call_modules.h"

extern long call_modules_ (char *, ftnlen);

int call_modules(char *arg) {
  long retval;
  ftnlen len;

  len = (ftnlen)strlen(arg);
  retval = call_modules_ (arg, len);
  return((int)retval);
}

/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : call_setdims
 */

#include <stdio.h>

extern long setdims_();

int call_setdims()
{
  long retval;

  retval = setdims_();
  if (retval) {
    fprintf(stderr,"ERROR in 'setdims' routine.\n");
    fprintf(stderr,"Return val = %ld\n", retval);
    return(1);
  }
  return(0);
}

/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : umalloc_etc
 * COMMENT  : memory allocation routines with error handling
 */

#include <stdlib.h>
#include <stdio.h>
#include "umalloc_etc.h"

/*--------------------------------------------------------------------*\
 | FUNCTION     : umalloc
\*--------------------------------------------------------------------*/
char *umalloc (unsigned size) {
  char *ptr;

  if (!size)
    return (NULL);

  if ((ptr = (char *)malloc(size)) == NULL)
    if (size != 0) {
      (void)fprintf(stderr, "Cannot perform malloc, size = %d\n",size);
      exit(1);
    }
  return(ptr);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : urealloc
\*--------------------------------------------------------------------*/
char *urealloc (char *ptr, unsigned size) {
  if (ptr == NULL) return(umalloc(size));
  if ((ptr = (char *)realloc(ptr, size)) == NULL)
    if (size != 0) {
      (void)fprintf(stderr, "Cannot perform realloc, size = %d\n",size);
      exit(1);
    }
  return(ptr);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : ucalloc
\*--------------------------------------------------------------------*/
char *ucalloc (unsigned num, unsigned size) {
  char *ptr;
  if ((ptr = (char *)calloc(num, size)) == NULL) 
    if ((size != 0) && (num != 0))
      (void)fprintf(stderr, "Cannot perform calloc, num, size = %d,%d\n",num,size);
      exit(1);
  return(ptr);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : ufree
\*--------------------------------------------------------------------*/
void ufree (char *ptr) {
}


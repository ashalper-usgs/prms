/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : decldim() to be called from C
 *            decldim_() to be called from Fortran
 *            declfix() to be called from C
 *            declfix_() to be called from Fortran
 * COMMENT  : initializes an entry in the dimension database
 */

#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "structs.h"
#include "protos.h"
#include "globals.h"

extern LIST *dim_db;		/* in alloc_space.c */
extern long Mdebuglevel;	/* in parse_args.c */

/*--------------------------------------------------------------------*\
 | FUNCTION     : decldim_
 | COMMENT	: called from Fortran, sorts out args and calls decldim()
\*--------------------------------------------------------------------*/
long decldim_ (char *dname, ftnint *dval, ftnint *dmax, char *ddescr, ftnlen namelen, ftnlen descrlen) {
	long value, max;
	char *name, *descr;
	long retval;

/*
* copy value & max into local long int
*/

	value = *dval;
	max = *dmax;

/*
* copy args to new strings, and terminate correctly
*/

	name = (char *) umalloc(namelen + 1);
	strncpy(name, dname, namelen);
	name[namelen] = '\0';

	descr = (char *) umalloc(descrlen + 1);
	strncpy(descr, ddescr, descrlen);
	descr[descrlen] = '\0';

/*
* call C version of decldim()
*/

	retval = decldim(name, value, max, descr);

	return(retval);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : decldim
 | COMMENT	: called from C
\*--------------------------------------------------------------------*/
long decldim (char *name, long value, long max, char *descr) {
	DIMEN *dim;

/*
* check that name does not already exist
*/

	dim = dim_addr(name);
   if (dim != NULL) {
		// This dimension has already been declared. Set the size to the
		// value of the last call.
		dim->value = value;

      return(0);
   }

   if (Mdebuglevel >= M_FULLDEBUG) {
      (void)fprintf(stderr, "Declaring dimension '%s'\n", name);
   }

/*
* check that default value is within limits
*/

   if(value < 0) {
      (void)fprintf(stderr, 
		    "ERROR - decldim - default dimension value negative.\n");
      (void)fprintf(stderr, "Name   :   '%s'\n", name);
      (void)fprintf(stderr, "Default:   %ld\n", value);
      return(1);
   }

   if(value > max) {
      (void)fprintf(stderr, 
        "ERROR - decldim - default dimension value exceeds max. allowed\n");
      (void)fprintf(stderr, "Name   :   '%s'\n", name);
      (void)fprintf(stderr, "Default:   %ld\n", value);
      (void)fprintf(stderr, "Max    :   %ld\n", max);
      return(1);
   }

/*
* allocate space for a structure, and store pointer in dimbase
*/
   dim = (DIMEN *) umalloc (sizeof(DIMEN));
   ADD_to_list (dim_db, (void *)dim);

/*
* allocate space, and store dimension properties
*/
   if (descr) dim->descr = strdup (descr);
   else dim->descr = NULL;

   if (name) dim->name = strdup (name);
   else dim->name = NULL;

   dim->value = value;
   dim->max = max;
   dim->names = NULL;
   dim->notes = NULL;
   dim->files = NULL;
   dim->format = NULL;
   dim->column_width = 10;
   dim->fixed = FALSE;
   dim->got = FALSE;

   sort_dims ();
   return(0);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : declfix
 | COMMENT	: Called from C to declare a fixed dimension.
\*--------------------------------------------------------------------*/
long declfix (char *name, long value, long max, char *descr) {
   long ret;

   ret = decldim (name, value, max, descr);
   ((DIMEN *)(dim_db->itm[dim_db->count - 1]))->fixed = TRUE;

   return (ret);
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : declfix_
 | COMMENT	: called from Fortran to declare a fixed dimension.
\*--------------------------------------------------------------------*/
long declfix_ (char *dname, ftnint *dval, ftnint *dmax, char *ddescr, ftnlen namelen, ftnlen descrlen) {
  long	ret;

  ret = decldim_ (dname, dval, dmax, ddescr, namelen, descrlen);
  ((DIMEN *)(dim_db->itm[dim_db->count - 1]))->fixed = TRUE;

  return (ret);
}

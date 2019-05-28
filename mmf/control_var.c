/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : control_var - generic, returns (char *) as a generic pointer
 *            control_lvar - returns long *
 *            control_fvar - returns float *
 *            control_dvar - returns double *
 *            control_svar - returns char ** - string
 *            returns pointers to various control array entries
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "structs.h"
#include "globals.h"
#include "control_addr.h"
#include "umalloc_etc.h"
#include "control_var.h"

/* in parse_args.c */
extern char *MAltContFile;

/*--------------------------------------------------------------------*\
  | FUNCTION     : control_var
  | COMMENT	: returns a pointer to the start of the variable
  |		  ( or first element in * the array) in a CONTROL struct
\*--------------------------------------------------------------------*/
char *control_var (char *key) {
 
  CONTROL *control;

  if ((control = control_addr(key)) == NULL) {
    (void)fprintf(stderr, 
		  "ERROR - control_var - key '%s' not found.\n", key);
    exit(1);
  }
  return (char *) control->start_ptr;
}

/*--------------------------------------------------------------------*\
  | FUNCTION    : control_lvar
  | COMMENT	: returns a pointer to a long variable
\*--------------------------------------------------------------------*/
long *control_lvar (char *key) {
  return ((long *) control_var(key));
}

/*--------------------------------------------------------------------*\
  | FUNCTION    : control_fvar
  | COMMENT	: returns a pointer to a float variable
\*--------------------------------------------------------------------*/
float *control_fvar (char *key) {
  return ((float *) control_var(key));
}

/*--------------------------------------------------------------------*\
  | FUNCTION    : control_dvar
  | COMMENT	: returns a pointer to a double variable
  \*--------------------------------------------------------------------*/
double *control_dvar (char *key) {
  return ((double *) control_var(key));
}

/*--------------------------------------------------------------------*\
  | FUNCTION    : control_svar
  | COMMENT	: returns a pointer to a string variable
\*--------------------------------------------------------------------*/
char **control_svar (char *key) {
  return ((char **) control_var(key));
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : control_string_
  | COMMENT	: called from Fortran
  \*--------------------------------------------------------------------*/
long control_string_ (char *retval, char *tag, ftnlen len, ftnlen tlen) {
  char *foo;

  foo = (char *) umalloc(tlen + 1);
  strncpy(foo, tag, tlen);
  foo[tlen] = '\0';

  memset (retval, ' ', len);
  strncpy (retval, *control_svar(foo), len);
  return 0;
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : control_string_array_
  | COMMENT	 : called from Fortran
\*--------------------------------------------------------------------*/
long control_string_array_ (char *retval, char *tag, int *index,
			    ftnlen len, ftnlen tlen) {
  char *foo;
  char **strings;
  int i;

  foo = (char *) umalloc(tlen + 1);
  strncpy(foo, tag, tlen);
  foo[tlen] = '\0';

  strings = (char **) control_var(foo);
  i = *index - 1;
  strncpy (retval, *(strings + i), len);
  return 0;
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : control_integer_
  | COMMENT	 : returns a long variable value
\*--------------------------------------------------------------------*/
long control_integer_ (int *retval, char *key, ftnlen len) {
  char *foo;

  foo = (char *) umalloc(len + 1);
  strncpy(foo, key, len);
  foo[len] = '\0';

  *retval = *control_var(foo);
  return 0;
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : control_integer_array_
  | COMMENT	 : called from fortran
\*--------------------------------------------------------------------*/
long control_integer_array_ (int *retval, int *index, char *key, ftnlen tlen) {
  char *foo;
  long intVal;
  long *longs;
  int i;

  foo = (char *) umalloc(tlen + 1);
  strncpy(foo, key, tlen);
  foo[tlen] = '\0';

  longs = (long *) control_var(foo);
  i = *index - 1;
  intVal = *(longs + i);
  *retval = (int)intVal;
  return 0;
}

/*--------------------------------------------------------------------*\
  | FUNCTION     : control_file_name_
  | COMMENT	 : called from Fortran
\*--------------------------------------------------------------------*/
long control_file_name_(char *retval, ftnlen tlen) {
  char *foo;

  foo = (char *)umalloc(tlen + 1);
  strncpy(foo, MAltContFile, tlen);
  foo[tlen] = '\0';
  memset(retval, ' ', tlen);
  strncpy(retval, foo, tlen);
  return 0;
}

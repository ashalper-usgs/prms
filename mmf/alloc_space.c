#include <string.h>
#include "structs.h"
#include "globals.h"
#include "defs.h"
#include "build_lists.h"
#include "decldim.h"
#include "umalloc_etc.h"
#include "alloc_space.h"

LIST *cont_db;
LIST *dim_db;
int max_vars;
PUBVAR **Mvarbase = NULL;   /* pointer to public variables database */
long Mnvars = 0;	    /* no of public variables in database */
int max_params;
PARAM **Mparambase = NULL;  /* pointer to parameter database */
long Mnparams = 0;	    /* no of params in database */
int max_read_vars;
READCHECK **Mcheckbase = NULL;	/* pointer to read check database */
long Mnreads = 0;	  /* max no. of calls to be made by readvar */
DATETIME *Mstrttime = NULL;	/* pointer to start time structure */
DATETIME *Mendtime = NULL;	/* pointer to end time structure */
DATETIME *Mnowtime = NULL; /* pointer to current data time structure */
DATETIME *Mnexttime = NULL;  /* pointer to next data time structure */
char *Mparaminfo = NULL;     /* pointer to param information string */
char *Mdatainfo = NULL;	     /* pointer to data information string */

void alloc_space (void) {
  static DATETIME start, end, now, next;

  cont_db = ALLOC_list ("Control Data Base", 0, 100);

  /*
   * space for the dimension pointer array
   */

  dim_db = ALLOC_list ("Dimension Data Base", 0, 50);

  /*
   * default dimension "one"
   */

  decldim ("one", 1, 1, "Dimension of scalar parameters and variables");

  /*
   * space for the public variable pointer array
   */

  max_vars = 500;
  Mvarbase = (PUBVAR **) umalloc (max_vars * sizeof(PUBVAR *));
  Mnvars = 0;

  /*
   * space for the parameter pointer array
   */

  max_params = 500;
  Mparambase = (PARAM **) umalloc (max_params * sizeof(PARAM *));
  Mnparams = 0;

  /*
   * space for the read check data base
   */

  max_read_vars = 50;
  Mcheckbase = (READCHECK **) umalloc (max_read_vars * sizeof(READCHECK *));
  Mnreads = 0;

  /*
   * space for time structures
   */
  Mstrttime = &start;
  Mendtime = &end;
  Mnowtime = &now;
  Mnexttime = &next;

  /*
   * space for run info. string
   */
  Mparaminfo = strdup ("Default case");
  Mdatainfo = strdup ("Default case");
}


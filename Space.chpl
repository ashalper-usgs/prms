/* U.S. Geological Survey
 *
 * File - Space.chpl
 *
 * Purpose - Allocate space for variables.
 *
 * Authors - Steve Markstrom, Steve Regan, Andrew Halper
 */

module Space {
//#define ALLOC_SPACE_C
//#include <string.h>
//#include "mms.h"
  use Structs;
  use Globals;
  use Lists;
  use Dimension;
  
  proc alloc_space (): void {
    var start, end, now, next: DATETIME;

    cont_db = ALLOC_list("Control Data Base", 0, 100);

    // space for the dimension pointer array

    max_dims = 50;
    // TODO:
    //Mdimbase = (DIMEN **) umalloc (max_dims * sizeof(DIMEN *));
    // TODO: need to find out where this is declared in PRMS 5:
    //Mndims = 0;

    dim_db = ALLOC_list("Dimension Data Base", 0, 50);

    // default dimension "one"

    decldim("one", 1, 1, "Dimension of scalar parameters and variables");

  /*
   * space for the public variable pointer array
   */

//  max_vars = 500;
//  Mvarbase = (PUBVAR **) umalloc (max_vars * sizeof(PUBVAR *));
//  Mnvars = 0;

/*
	var_db = ALLOC_list ("Variable data base", 0, 100);
*/

  /*
   * space for the parameter pointer  array
   */

//  max_params = 500;
//  Mparambase = (PARAM **) umalloc (max_params * sizeof(PARAM *));
//  Mnparams = 0;
/*
	param_db = ALLOC_list ("Paraameter data base", 0, 100);
*/

  /*
   * space for the read check data base
   */

//  max_read_vars = 50;
//  Mcheckbase = (READCHECK **) umalloc (max_read_vars * sizeof(READCHECK *));
//  Mnreads = 0;

/*
	read_var_db = ALLOC_list ("Paraameter data base", 0, 100);
*/

/*
* space for time structures
*/
//	Mstrttime = &start;
//	Mendtime = &end;
//	Mnowtime = &now;
//	Mnexttime = &next;

/*
* space for run info string
*/
//	Mparaminfo = strdup ("Default case");
//	Mdatainfo = strdup ("Default case");
  }

} // Space

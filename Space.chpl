/*
 * United States Geological Survey
 *
 * File - Space.chpl
 *
 * Purpose - Allocate space for variables.
 *
 * Authors - Steven Markstrom, Steve Regan, Andy Halper
 */

module Space {
  proc alloc () {
    // TODO:
    //    static DATETIME start, end, now, next;

    use Globals;
    use PRMSList;
    cont_db = PRMSList.alloc("Control Data Base", 0, 100);

    // space for the dimension pointer array
    dim_db = PRMSList.alloc("Dimension Data Base", 0, 50);

    // default dimension "one"
    //  decldim ("one", 1, 1, "Dimension of scalar parameters and variables");

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
  } // alloc
} // Space

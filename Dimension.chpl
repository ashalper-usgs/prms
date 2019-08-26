/* U.S. Geological Survey
 *
 * File - Dimension.chpl
 *
 * Purpose - Initializes an entry in the dimension database.
 *
 * Authors - Steven Markstrom, Andrew Halper.
 */

module Dimension {

  record Type {
    var name: string;
    var value: int;
    var max: int;
    var descr: string;
    var names: [1..0] string;
    var notes: [1..0] string;
    var Files: [1..0] file;
    var column_width: int;
    var format: string;
    var fixed: int;
    var got: int;
  }

  use Globals;

  proc declare(name: string, value: int, max: int, descr: string): int {
    var dim: Dimension.Type;

    // check that name does not already exist

    dim = addr(name);
    if dim != nil then {
      // This dimension has already been declared. Set the size to the
      // value of the last call.
      dim.value = value;

      return 0;
    }

    if Mdebuglevel >= M_FULLDEBUG then {
      stderr.write("Declaring dimension '%s'\n", name);
   }

    // check that default value is within limits

    if value < 0 then {
      stderr.write(
	"ERROR - Dimension.declare() - default dimension value negative.\n"
      );
      stderr.write("Name   :   '%s'\n", name);
      stderr.write("Default:   %ld\n", value);
      return 1;
    }

//   if(value > max) {
//      (void)fprintf(stderr, 
//        "ERROR - decldim - default dimension value exceeds max. allowed\n");
//      (void)fprintf(stderr, "Name   :   '%s'\n", name);
//      (void)fprintf(stderr, "Default:   %ld\n", value);
//      (void)fprintf(stderr, "Max    :   %ld\n", max);
//      return(1);
//   }

/*
* allocate space for a structure, and store pointer in dimbase
*/
//   dim = (DIMEN *) umalloc (sizeof(DIMEN));
//   ADD_to_list (dim_db, (void *)dim);

/*
* allocate space, and store dimension properties
*/
//   if (descr) dim->descr = strdup (descr);
//   else dim->descr = NULL;

//   if (name) dim->name = strdup (name);
//   else dim->name = NULL;

//   dim->value = value;
//   dim->max = max;
//   dim->names = NULL;
//   dim->notes = NULL;
//   dim->files = NULL;
//   dim->format = NULL;
//   dim->column_width = 10;
//   dim->fixed = FALSE;
//   dim->got = FALSE;

//   sort_dims ();
    return 0;
}

/*--------------------------------------------------------------------*\
 | FUNCTION     : declfix
 | COMMENT		: Called from C to declare a fixed dimension.
 | PARAMETERS   :
 | RETURN VALUE : 
 | RESTRICTIONS :
\*--------------------------------------------------------------------*/
//long declfix (char *name, long value, long max, char *descr) {
//   long ret;

//   ret = decldim (name, value, max, descr);
//   ((DIMEN *)(dim_db->itm[dim_db->count - 1]))->fixed = TRUE;

//   return (ret);
//}

  proc addr(name: string): LIST {
    if (dim_db.count == 0) then
      // TODO: might be insufficient, due to incompatability with
      // legacy code
      throw new owned Error();

    for itm in dim_db.itm do
      if (itm.name == name) then
	return itm;

    throw new owned Error();
  }

//char *dim_notes (char *ch_ptr) {
//	int		i, j;
//	DIMEN	*dim;

//	for (i = 0; i < dim_db->count; i++) {
//		dim = (DIMEN *)(dim_db->itm[i]);
//		for (j = 0; j < dim->value; j++)
//			if (dim->names && dim->names[j] && (!strcmp (dim->names[j],ch_ptr)))
//				return (dim->notes[j]);
//	}

//	return (NULL);
//  }

} // Dimension

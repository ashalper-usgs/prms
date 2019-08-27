/* U.S. Geological Survey
 *
 * File - Lists.chpl
 *
 * Purpose - List data types for PRMS.
 *
 * Authors - Steve Markstrom, Steve Regan, Andrew Halper
 */

module Lists {
  // #include "mms.h"
  use Structs;
  
  const INPUT: int = 1;
  const OUTPUT: int = 2;

  proc ALLOC_list(name: string, typ: int, size: int) {
    // TODO: "void" is a place-holder type here.
    var list: LIST(void, void);

    list.name = name;

    list.size = size;
    list.count = 0;
    list.typ = typ;
    list.raus = false;

    return list;
  }

//void DELETE_list (LIST *list) {

//	int		i;

//	if (list->name)
//		free (list->name);

//	for (i = 0; i < list->count; i++)
//		if (list->itm[i])
//			free (list->itm[i]);

//	free (list->itm);
//	free (list);
//}

//void RESIZE_list (LIST *list, int new_size) {
//	list->size = new_size;
//	list->itm = (void **)realloc (list->itm, new_size * sizeof (void *));
//}

//void ADD_to_list (LIST *list, void *itm) {
//	if (list->count >= list->size)
//		RESIZE_list (list, list->size + 100);

//	list->itm[list->count++] = itm;
//}

} // Lists

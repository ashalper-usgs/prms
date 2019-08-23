/*
 * United States Geological Survey
 *
 * File - NHMList.chpl
 *
 * Purpose - List utility functions.
 *
 * Authors - Steven Markstrom, Steve Regan, Andrew Halper
 */

module NHMList {
  const input: int = 1;
  const output: int = 2;

  use Control;
  union ElementType {
    var user_data: ControlType;
  }

  use LinkedLists;
  record ListType {
    var name: string;
    var size: int;		// headroom; legacy artifact
    var count: int;		// number of elements in list
    var typ: int;		// "type" in PRMS 5
    var ot: bool;		// "out" in PRMS 5
    var linked_list: LinkedList(ElementType);
  }

  proc alloc(name: string, typ: int, size: int): ListType {
    var list: ListType;

    // TODO: might not be necessary
    // list = (LIST *)malloc (sizeof (LIST));

    if (0 < name.length) then
      list.name = name;
    else
      list.name = "";

    list.size = size;
    list.count = 0;
    list.typ = typ;
    list.ot = false;

    // TODO: might not be necessary
    //	list.user_data = NULL;

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

  // TODO: no-op legacy artifact; try to factor out
  proc resize(list: ListType, new_size: int) {
    list.size = new_size;
  }

  proc add_to(list: ListType, element: ElementType) {
    if list.count >= list.size then
      resize(list, list.size + 100);

    list.linked_list.push_back(element);
  }

} // NHMList

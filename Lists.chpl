/* U.S. Geological Survey
 *
 * File - Lists.chpl
 *
 * Authors - Steven Markstrom, Andrew Halper
 */

module Lists {

  record LIST {
    var name: string;
    var size: int;
    var count: int;
    var typ: int;
    var ut: bool;
    // TODO: "void" is a place-holder here; need actual types
    var user_data: void;
    var itm: void;
  }
 
  proc alloc (name: string, typ: int, size: int): LIST {
    var list: LIST;

    list.name.init(name, true);

    list.size = size;
    list.count = 0;
    list.typ = typ;
    list.ut = false;
    // TODO:
    //list.user_data = NULL;

    /*
      TODO: may no longer be necessary

    if (0 < size)
      list.itm = (void **)malloc (size * sizeof (void *));
    else 
      list.itm = NULL;
    */
    return list;
  }

  proc del (list: LIST): void {
    /* TODO: probably no longer necessary or need to completely
       re-write

    if (list.name)
      free (list.name);

    for (i = 0; i < list.count; i++)
      if (list.itm[i])
      free (list.itm[i]);

    free (list.itm);
    free (list);
    */
    return;
  }

  proc resize (list: LIST, new_size: int): void {
    list.size = new_size;
    /*
      TODO: probably no longer necessary or need to re-write

    list.itm = (void **)realloc (list.itm, new_size * sizeof (void *));
    */
    return;
  }

  proc add_to (list: LIST, itm): void {
    if (list.count >= list.size) then
      resize (list, list.size + 100);

    list.count += 1;
    list.itm[list.count] = itm;
    return;
  }
  
} // Lists

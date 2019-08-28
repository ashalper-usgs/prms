module Structs {

  record LIST {
    var name: string;
    var size: int;
    var count: int;
    var typ: int;
    var raus: bool;
    var user_data;
    var itm: LinkedList(?t);
  };

} // Structs

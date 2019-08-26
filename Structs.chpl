/* U.S. Geological Survey
 *
 * File - Structs.chpl
 *
 * Purpose - Data type declarations for PRMS.
 *
 * Authors - Steven Markstrom, Andrew Halper.
 */

module Structs {
  // dimension
  record DIMEN {
    var name: string;
    var value: int;
    var max: int;
    var descr: string;
    var names: [1..0] string;	// TODO: needs Chapel array domain
    var notes: [1..0] string;	// TODO: needs Chapel array domain
    var files: [1..0] file;	// TODO: needs Chapel array domain
    var column_width: int;
    var format: string;
    var fixed: int;
    var got: int;
  }

//typedef struct {
//  char *key;
//  char *module;
//  char *name;
//  long ndimen;
//  long pf_ndimen;
//  struct dimen_t **dimen;
//  char **pf_dimNames;
//  long size;
//  long pf_size;
//  long type;
//  long bound_status;
//  struct dimen_t *bound_dimen;
//  char *value;
//  char *min;
//  char *max;
//  char *def;
//  char *descr;
//  char *help;
//  char *units;
//  char *format;
//  long column_width;
//  char *value_string;
//  char *min_string;
//  char *max_string;
//  char *def_string;
//  long read_in;
//  void **references;
//  long num_references;
//  long size_references;
//  long preprocess;
//} PARAM;                 /* parameter pointer structure */

  // control variable class
  record CONTROL {
    var key: string;
    var size: int;
    var typ: int;
    var start_ptr;
    var set_in_file: int;
  };

//typedef struct {
//  long year, month, day, hour, min, sec, jd;
//  double jt;
//} DATETIME;                 /* date and time structure */

  // TODO: this is a place-holder until we find out what user_data
  // (void *) was used for in the PRMS 5 C source.
  record UserData {
    var x: int;
  }

  class LIST {
    var name: string;
    var size: int;
    var count: int;
    var typ: int;
    var ot: bool;
    var user_data;
    var itm;

    proc init(name: string, typ: int, size: int, type t) {
      this.name = name;
      this.size = size;
      this.count = 0;
      this.typ = typ;
      this.ot = false;
      this.user_data = new UserData(0);
      this.itm = new LinkedList(t);
    }
  } // LIST

  // public variable record
  record PUBVAR {
    var key: string;
    var module_name: string;
    var name: string;
    var ndimen: int;
    var dimen: DIMEN;
    var size: int;
    var typ: int;
    var help: string;
    var units: string;
    var value: string;
    var privat: int;
  };

//typedef struct {
//  PUBVAR *var;
//  long count;
//  union {
//    long   * valuel;
//    float  * valuef;
//    double * valued;
//  }Types;
//} READCHECK; /* for checking the readvar function calls */

//typedef struct file_data_t {
//	FILE    *fp;
//	char    *name;
//	char    line[MAXDATALNLEN];
//	char    *line;
//	char    *start_of_data;
//	float   delta_t;
//	char    info[MAXDATALNLEN];
//	char    *info;
//	DATETIME    time;
//} FILE_DATA;

//typedef struct STAT_LIST_TYPE {
//  char key[MAXDATALNLEN];
//	char *key;
//	char *element;
//    long type;
//    char *value;
//    struct STAT_LIST_TYPE *next;
//} STAT_LIST_TYPE;   /* linked list element of stat vars */

//typedef struct module_data_t {
//	char    *name;
//	char    *version;
//	LIST    *params;
//	LIST    *vars;
//} MODULE_DATA;

}
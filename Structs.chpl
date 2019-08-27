/* U.S. Geological Survey
 *
 * File - Structs.chpl
 *
 * Purpose - Data structure definitions for PRMS.
 *
 * Authors - Steve Markstrom, Steve Regan, Andrew Halper
 */

module Structs {
//#ifndef _STRUCTS_H
//#define _STRUCTS_H

//#include <stdio.h>

  // dimension structure
  record DIMEN {
    var name: string;
    var value: int;
    var max: int;
    var descr: string;
    var names: [1..0] string;
    var notes: [1..0] string;
    var files: [1..0] file;
    var column_width: int;
    var format: string;
    var fixed: int;
    var got: int;
  };

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
//  //char **value_desc;
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

  // control variable structure
  record CONTROL {
    var key: string;
    var size: int;
    var typ: int;
    // TODO: might not be necessary
    var start_ptr: void;
    var set_in_file: int;
  };

  // date and time structure
  record DATETIME {
    var year, month, day, hour, min, sec, jd: int;
    var jt: real;
  };

  record LIST {
    var name: string;
    var size: int;
    var count: int;
    var typ: int;
    var raus: bool;
    var user_data;
    var itm;
  };

//typedef struct {
//  char *key;
//  char *module;
//  char *name;
//  long ndimen;
//  struct dimen_t **dimen;
//  long size;
//  long type;
//  char *help;
//  char *units;
//  char *value;
//  int private;
//} PUBVAR;                 /* public variable pointer structure */

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
//	char    *line;
//	char    *start_of_data;
//	float   delta_t;
//	char    *info;
//	DATETIME    time;
//} FILE_DATA;

//typedef struct STAT_LIST_TYPE {
//	char *key;
//	char *element;
//    long type;
//    char *value;
//    struct STAT_LIST_TYPE *next;
//} STAT_LIST_TYPE;   /* linked list element of stat vars */

  record MODULE_DATA {
    var name: string;
    var version: string;
    var params: void;		// LIST?
    var vars: void;		// LIST?
  };

//#endif
} // Structs

/* U.S. Geological Survey
 *
 * File - PRMS.chpl
 *
 * Purpose - Main program for PRMS.
 *
 * Authors - Andrew Halper, Steven Markstrom
 */

// TODO: need to see if there's a way to make a type alias in Chapel
//#define ftnint int
//#define ftnlen int

const M_LONG: int = 1;
const M_FLOAT: int = 2;
const M_DOUBLE: int = 3;
const M_STRING: int = 4;

const M_PARAMETER: int = 0;
const M_VARIABLE: int = 1;

const M_BOUNDED: int = 1;
const M_UNBOUNDED: int = 2;

const ERROR_TIME: int = 100;
const M_FULLDEBUG: int = 2;

// TODO: translate to proc (or translate to Chapel built-in)?
//#ifndef MIN
//#define MIN(a,b) (a < b) ? a : b
//#endif

//#ifndef MAX
//#define MAX(a,b) (a > b) ? a : b
//#endif

// max number of characters in input file line
const MAXDATALNLEN: int = 12000;

// TODO:
//#define ENDOFFILE 2L
//#define ENDOFDATA 1L
//#define NOTENDOFDATA 0l

const MAXCTRLLINELEN: int = 256; // max. length of a line in a Control File
const MAXPATHLEN: int = 256;	// max. number of characters in a path

const MAX_NDIMEN: int = 3; // max number of dimensions for a variable or parameter
const MAXVARLEN: int = 32; // max number of characters in variable string

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
}

// parameter structure
record PARAM {
  var key: string;
  var mod: string;
  var name: string;
  var ndimen: int;
  var pf_ndimen: int;
  var dimen: DIMEN;
  var pf_dimNames: [1..0] string;
  var size: int;
  var pf_size: int;
  var typ: int;
  var bound_status: int;
  var bound_dimen: DIMEN;
  var value: string;
  var min: string;
  var max: string;
  var def: string;
  var descr: string;
  var help: string;
  var units: string;
  var format: string;
  var column_width: int;
  var value_string: string;
  var min_string: string;
  var max_string: string;
  var def_string: string;
  var read_in: int;
  var references;
  var num_references: int;
  var size_references: int;
  var preprocess: int;
}

// control variable structure
record CONTROL {
  var key: string;
  var size: int;
  var typ: int;
  var start_ptr;
  var set_in_file: int;
}

// datetime structure
record DATETIME {
  var year, month, day, hour, min, sec, jd: int;
  var jt: real;
}

record LIST {
  var name: string;
  var size: int;
  var count: int;
  var typ: int;
  var ut: int;
  var user_data;
  var itm;
}

// public variable structure
record PUBVAR {
  var key: string;
  var mod: string;
  var name: string;
  var ndimen: int;
  var dimen;
  var size: int;
  var typ: int;
  var help: string;
  var units: string;
  var value: string;
  var privat: int;
}

// for checking the readvar function calls
record READCHECK {
  var v: PUBVAR;
  var count: int;
  union Types {
    var valuel: int;
    var valuef: real;
    var valued: real;
  }
}

record FILE_DATA {
  var fp: file;
  var name: string;
  var line: string;
  var start_of_data: string;
  var delta_t: real;
  var info: string;
  var time: DATETIME;
}

/* list element of stat vars */
record STAT_LIST_TYPE {
  var key: string;
  var element: string;
  var typ: int;
  var value: string;
  var next: STAT_LIST_TYPE;
}

record MODULE_DATA {
  var name: string;
  var version: string;
  var params: LIST;
  var vars: LIST;
}

var max_data_ln_len: int;
var MAltContFile: string;
var Mdebuglevel: int;
var model_name: string;
var executable_model: string;
var batch_run_mode: int;
var run_period_of_record: int;
var print_mode: int;
var runtime_graph_on: int;
var preprocess_on: int;
var cont_db: LIST;
var dim_db: LIST;
var module_db: LIST;
var current_module: MODULE_DATA;
var Mvarbase: [1..0] PUBVAR;
var Mnvars: int;
var Mparambase: [1..0] PARAM;
var Mnparams: int;
var Mcheckbase: [1..0] READCHECK;
var Mnreads: int;
var Mstrttime: DATETIME;
var Mendtime: DATETIME;
var Mnowtime: DATETIME;
var Mnexttime: DATETIME;
var Mparaminfo: string;
var Mdatainfo: string;
var unsort_params: [1..0] PARAM;
var fd: [1..0] FILE_DATA;
var Mnsteps: int;
var Mprevjt: real;
var Mdeltat: real;
var Minpptr: string;
var Mdeltanext: real;
var M_stop_run: int;
var Mfirst_stat_list: STAT_LIST_TYPE;
var Mtypes: [1..0] string;
var ParamBaseIsDirty: int;
var max_vars: int;
var max_params: int;
var max_read_vars: int;
var max_dims: int;
var max_controls: int;

proc main (argv: [] string): int {
  var max_data_ln_len: int; // now possible to set this on command line
  var MAltContFile: string = ""; // Alt. name of control file
  var Mdebuglevel: int = 0;	 // the current debug level
  var model_name: string = "";
  var executable_model: string = "";
  var batch_run_mode: bool = false; // flag for running in batch mode
  var run_period_of_record: bool = false; // flag for running entire period of record in batch mode
  var print_mode: bool = false;
  var runtime_graph_on: bool = false;
  var preprocess_on: bool = false; // flag for running in preprocess mode
  var cont_db: LIST;
  var dim_db: LIST;
  var module_db: LIST;
  var current_module: MODULE_DATA;
  var Mvarbase: [1..0] PUBVAR; // pointer to public variables database
  var Mnvars: int = 0;	       // no of public variables in database
  var Mparambase: [1..0] PARAM;	// pointer to parameter database
  var Mnparams: int = 0;	// no of parameters in database
  var Mcheckbase: [1..0] READCHECK; // pointer to read check database
  var Mnreads: int = 0;	   // max. no of calls to be made by readvar
  var Mstrttime: DATETIME; // pointer to start time structure
  var Mendtime: DATETIME;  // pointer to end time structure
  var Mnowtime: DATETIME;  // pointer to current data time structure
  var Mnexttime: DATETIME; // pointer to next datetime structure
  var Mparaminfo: string = ""; // pointer to parameter information string
  var Mdatainfo: string = "";  // pointer to data information string
  var unsort_params: [1..0] PARAM; // pointer to unsorted parameters
  var fd: [1..0] FILE_DATA;
  var Mnsteps: int = 0;		// the number of steps so far
  var Mprevjt: real = -1.0;	// the latest previous Julian time
  var Mdeltat: real = 0.0;	// the latest time step in hours
  var Minpptr: string = ""; // pointer to current position in data input line
  var Mdeltanext: real = 0.0; // the latest next time step in hours
  var M_stop_run: int = 0;    // Run switch 0 -or 1
  var Mfirst_stat_list: STAT_LIST_TYPE;	// pointer to first entry in
					// stats linked list
  var Mtypes = ["", "long", "float", "double", "string", "", "","", "", ""];
  var ParamBaseIsDirty: bool = false;
  var max_vars: int;
  var max_params: int;
  var max_read_vars: int;
  var max_dims: int;
  var max_controls: int;

  var set_count: int;
  var i, j: int;
  var set_name, set_value: [1..set_size] string;
  var cp: CONTROL;
  var cptr: string;
  ref dptr: real;
  ref fptr: real;
  ref lptr: int;
  ref cpt: string;
  /* TODO: */
  //struct stat stbuf;
  var buf: string;
  var err: string;
  var num_param_files: int = 0;
  var fname: [1..0] string;
  var pathname: string;
  var set_size: int;

  /*
    Maximum buffer size for reading lines from files. This used to be
    set as a C precompiler directive. That is still the default, but
    now users are give. the option to set this on the command line,
    otherwise size still comes from the defs.h file.
  */
  max_data_ln_len = MAXDATALNLEN;

  /*
    List of modules that are used by the model. This is determined by
    calls to declmodule.
  */
  module_db = ALLOC_list ("Module Data Base", 0, 100);

  // parse the command-line arguments
  set_count = 0;
  set_size = 100;
  parse_args (argv, set_count, set_name, set_value, set_size);

  if (MAltContFile == "") {
    stderr.write("Usage: Set the full path to the control file using the '-C' option.\n\n");
    exit(0);
  }

  alloc_space ();

  setup_cont ();
  err = read_control (MAltContFile);
  if (err) {
    stderr.write("%s\n", err);
    exit (1);           
  }

  fname = control_svar ("param_file");
  num_param_files = control_var_size ("param_file");

  /* TODO: parsing loop here probably needs work */
  for i in 0..set_count do {
    cp = control_addr (set_name[i]);
    if (0 < cp.length) {

      stderr.write("\nControl variable %s set to %s.\n\n",
		   set_name[i], set_value[i]);

      j = 0;
      for cptr in split(set_value[i], ",") do {
	if (cp.typ == M_DOUBLE) {
	  dptr = cp.start_ptr;
	  dptr[j] = atof(cptr);
	} else if (cp.typ == M_FLOAT) {
	  fptr = cp.start_ptr;
	  fptr[j] = cptr:real;
	} else if (cp.typ == M_LONG) {
	  lptr = cp.start_ptr;
	  lptr[j] =  cptr:int;
	} else if (cp.typ == M_STRING) {
	  cpt = cp.start_ptr;
	  cpt[j].init(cptr, true);
	}

	j += 1;
      }

    } else {
      stderr.write("\nControl variable %s not found -- ignored.\n\n", set_name[i]);
    }
  }

  fname = control_svar ("param_file");
  num_param_files = control_var_size ("param_file");

  if (call_setdims()) {
    stderr.write("\nERROR: Calling function 'call_setdims'\n");
    exit (1);
  }

  // read dimension info from parameter file
  if (stat (*control_svar("param_file"), &stbuf) != -1) {
    if (stbuf.st_size) {
    } else {
      stderr.write(buf, "Parameter File: %s is empty.",
		   *control_svar("param_file"));
      exit (1);
    }
  }
    
  err = read_dims (*control_svar("param_file"));
  if (err) {
    fprintf (stderr,"\n%s\n", err);
    exit (1);
  }

  fname = control_svar ("param_file");
  num_param_files = control_var_size ("param_file");

  if (call_modules("declare")) {
    (void)fprintf(stderr, "\nERROR: in declare procedure, in function 'call_modules'\n");
    exit (1);
  }
    
  // read in parameter values from parameter file
  fname =   control_svar ("param_file");
  num_param_files = control_var_size ("param_file");

  /*
    Look for, declare and read in mapping parameters before any of
    the "module" parameters.
  */
  for (i = 0; i < num_param_files; i++) {
    if (stat (fname[i], &stbuf) != -1) {
      if (stbuf.st_size) {
      } else {
	(void)fprintf (stderr,buf, "ERROR: Parameter file: %s is empty.",
		       fname[i]);
	exit (1);
      }
    }
	    
    err = read_params (fname[i], i, 1);
    if (err) {
      (void)fprintf (stderr,"\n%s\n", err);
      exit (1);
    }
  }

  // Read in the parameters declared by the modules.
  for (i = 0; i < num_param_files; i++) {
    if (stat (fname[i], &stbuf) != -1) {
      if (stbuf.st_size) {
      } else {
	(void)fprintf (stderr,buf, "ERROR: Parameter file: %s is empty.",
		       fname[i]);
	exit (1);
      }
    }
	    
    err = read_params (fname[i], i, 0);
    if (err) {
      (void)fprintf (stderr,"\n%s\n", err);
      exit (1);
    }
  }
    
  // get data info string into the global
  err = READ_data_info ();
  if (err) (void)fprintf (stderr,"\nMMS - Warning: %s", err);

  // get start and end time
  get_times ();
    
  if (print_mode) {
    print_params();
    print_vars();
    print_model_info();
    (void)snprintf (pathname, MAXPATHLEN, "%s.param", MAltContFile);
    save_params (pathname);

  } else {

    BATCH_run ();
    ;
  }

  exit (0);
}

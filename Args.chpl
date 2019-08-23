/*
 * United States Geological Survey
 *
 * File - Args.chpl
 * 
 * Purpose - Parse command line arguments.
 *
 * Authors - Steven Markstrom, Andrew Halper
 */

module Args {
  proc parse(args: [] string, set_count: int, set_name: string,
	     set_value: string, set_size: int) {
    var i: int;
    var ptr: int;

    // get the model name
    ptr = args[0].find("/");
    if (ptr == 0) then
      ptr = args[0].find("\\");
    ptr += 1;

    use Globals;
    model_name = args[0](ptr..args[0].length);
    executable_model = args[0].replace(".exe", "");

    if (args.size >= 2) then {
      for i in 1..args.size - 1 do {
	select (args[i]) {
	when "-debug" do {
	  try {
	    Mdebuglevel = args[i + 1]:int;
	  }
	  catch {
	    writeln("could not parse -debug level");
	  }
	}
	when "-C" do MAltContFile = args[i];
	when "-batch" do batch_run_mode = true;
	when "-print" do print_mode = true;
	when "-por" do run_period_of_record = true;
	when "-rtg" do runtime_graph_on = true;
	when "-preprocess" do preprocess_on = true;
	when "-set" do {
	  if (set_count >= set_size) then {
	    writeln("Args.parse: Overflow. Too many command line " +
		    "arguments set with -set flag.\n\n\n");
	    exit(1);
	  }
	  // TODO: see PRMS 5, parse_args.c
//            i++;
//            *(set_name + *set_count) = strdup ((char *)((argv[i])));
//            i++;
//            *(set_value + *set_count) = strdup ((char *)((argv[i])));
//            (*set_count)++;

	}
	when "-MAXDATALNLEN" do {
	  try {
	    max_data_ln_len = args[i + 1]:int;
	  }
	  catch {
	    writeln("could not parse -MAXDATALNLEN value");
	  }
	 }
	} // select (args[i])
	// assume argument with no flag is control file name
	MAltContFile = args[args.size - 1];
      }
    }
  } // parse
} // Args

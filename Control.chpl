/* U.S. Geological Survey
 *
 * File - Control.chpl
 *
 * Purpose - Set up PRMS model control.
 *
 * Authors - Steven Markstrom, Andrew Halper
 */

//extern void decl_control_string (char *key, char *valstr);
//extern void decl_control_int_array (char *key, long size, long *valstr);
//extern void decl_control_float_array (char *key, long size, float *valstr);
//extern void decl_control_string_array (char *key, long size, char *valstr);

module Control {

  record ControlType {
    var key: string;
    var size: int;
    var typ: int;
    // TODO:
    //void *start_ptr;
    var set_in_file: int;
  }

  proc setup (void) {
    var lval: int;
    var fval: real;

    const Minute = {1..6};

    const StartDate: [Minute] int;
    StartDate.push_back(2000).push_back(10).push_back(1);
    for i in 1..3 do StartDate.push_back(0);

    const EndDate: [Minute] int;
    EndDate.push_back(2001).push_back(9).push_back(30);
    for i in 1..3 do EndDate.push_back(0);

    const Modflow0Date: [Minute] int;
    Modflow0Date.push_back(-999).push_back(9).push_back(30);
    for i in 1..3 do Modflow0Date.push_back(0);

    // GSFLOW control variables
    decl_control_string("model_mode", "PRMS");
    decl_control_string("modflow_name", "modflow.nam");
    decl_control_string("precip_module", "precip_1sta");
    decl_control_string("temp_module", "temp_1sta");
    decl_control_string("et_module", "potet_jh");
    decl_control_string("srunoff_module", "srunoff_smidx");
    decl_control_string("solrad_module", "ddsolrad");
    decl_control_string("soilzone_module", "soilzone");
    decl_control_string("capillary_module", "soilzone");
    decl_control_string("strmflow_module", "strmflow");
    decl_control_string("transp_module", "transp_tindex");
    decl_control_string("gsflow_output_file", "gsflow.out");
    decl_control_string("gsflow_csv_file", "gsflow.csv");
    decl_control_string("creator_email", "unknown");

    // TODO: seems like legacy code might be doing some elaborate
    // casting here; need to find out if it's still needed.

    //        lval = (long *)umalloc (sizeof (long));
    //		lval[0] = 7;
    //        decl_control_int_array ("rpt_days", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 1;
//        decl_control_int_array ("gsf_rpt", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("print_debug", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 1;
//		decl_control_int_array ("cascade_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 1;
//		decl_control_int_array ("cascadegw_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 1;
//		decl_control_int_array ("subbasin_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("gwr_swale_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("frozen_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dprst_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 1;
//		decl_control_int_array ("parameter_check_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 1;
//		decl_control_int_array ("cbh_check_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("cbh_binary_flag", 1, lval);		

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_imperv_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_intcp_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_covden_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_sro2dprst_perv_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_sro2dprst_imperv_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_covtype_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_transp_flag", 1, lval);

//		lval = (long *)umalloc(sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array("dyn_transp_on_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_fallfrost_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_springfrost_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_potet_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_soil_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_radtrncf_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array("dyn_snareathresh_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_sro_to_dprst_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_sro_to_imperv_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dyn_dprst_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("stream_temp_flag", 1, lval);

//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 0;
//		decl_control_int_array("strmtemp_humidity_flag", 1, lval);
		
//		lval = (long *)umalloc(sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array("stream_temp_shade_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("segment_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("gwr_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("external_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("consumed_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("lake_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("dprst_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("soilzone_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("canopy_transferON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("seg2hru_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("glacier_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("mbInit_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("musroute_flag", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("orad_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("snow_cbh_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("gwflow_cbh_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("humidity_cbh_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("windspeed_cbh_flag", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//		decl_control_int_array ("segmentOutON_OFF", 1, lval);

//		lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("ignore_data_file_end", 1, lval);
/*
**	file names
*/
//        decl_control_string ("executable_desc", "MOWS executable");
//        decl_control_string ("executable_model", "prmsIV");
//        decl_control_string ("data_file", "prms.data");
//        decl_control_string ("param_file", "prms.params");
//        decl_control_string ("var_save_file", "prms_ic.out");
//        decl_control_string ("var_init_file", "prms_ic.in");
//        decl_control_string ("stat_var_file", "statvar.out");
//        decl_control_string ("ani_output_file", "animation.out");
//        decl_control_string ("model_output_file", "prms.out");
//        decl_control_string ("stats_output_file", "stats.out");
//		decl_control_string ("tmax_day", "tmax.day");
//        decl_control_string ("tmin_day", "tmin.day");
//        decl_control_string ("precip_day", "precip.day");
//        decl_control_string ("swrad_day", "swrad.day");
//        decl_control_string ("potet_day", "potet.day");
//        decl_control_string ("transp_day", "transp.day");
//        decl_control_string ("windspeed_day", "windspeed.day");
//        decl_control_string ("humidity_day", "humidity.day");
//		decl_control_string ("pkwater_equiv_day", "pkwater_equiv.day");
//        decl_control_string ("pk_depth_day", "pk_depth.day");
//        decl_control_string ("snow_evap_day", "snow_evap.day");
//        decl_control_string ("snowcov_area_day", "snowcov_area.day");
//        decl_control_string ("snowmelt_day", "snowmelt.day");
//        decl_control_string ("gwres_flow_day", "gwres_flow.day");
//        decl_control_string ("dprst_area_dynamic", "dyndprst_area");
//        decl_control_string ("dprst_depth_dynamic", "dyndprst_depth");
//        decl_control_string ("dprst_frac_dynamic", "dyndprst_frac");
//		decl_control_string ("snow_intcp_dynamic", "dynsnowintcp");
//		decl_control_string ("srain_intcp_dynamic", "dynsrainintcp");
//		decl_control_string ("wrain_intcp_dynamic", "dynwrainintcp");
//		decl_control_string ("imperv_frac_dynamic", "dynimperv");
//		decl_control_string ("imperv_stor_dynamic", "dynimperv");
//		decl_control_string ("covtype_dynamic", "dyncovtype");
//		decl_control_string ("covden_sum_dynamic", "dyncovden_sum");
//		decl_control_string ("covden_win_dynamic", "dyncovden_win");
//		decl_control_string ("jhcoef_dynamic", "dynjhcoef");
//		decl_control_string ("potet_coef_dynamic", "dynpotetcoef");
//		decl_control_string ("transpbeg_dynamic", "dyntranspbeg");
//		decl_control_string ("transpend_dynamic", "dyntranspend");
//		decl_control_string ("fallfrost_dynamic", "dynfallfrost");
//		decl_control_string ("springfrost_dynamic", "dynspringfrost");
//		decl_control_string ("soilrechr_dynamic", "dynsoilrechr");
//		decl_control_string ("soilmoist_dynamic", "dynsoilmoist");
//		decl_control_string ("radtrncf_dynamic", "dynradtrncf");
//		decl_control_string ("sro2dprst_perv_dynamic", "dynsro2dprst_perv");
//		decl_control_string ("sro2dprst_imperv_dynamic", "dynsro2dprst_imperv");
//		decl_control_string ("transp_on_dynamic", "dyntranspon");
//		decl_control_string ("csv_output_file", "prms_summary.csv");
//        decl_control_string ("nhruOutBaseFileName", "nhruout_path");
//		decl_control_string ("nsubOutBaseFileName", "nsubout_path");
//		decl_control_string ("basinOutBaseFileName", "basinout_path");
//		decl_control_string("nsegmentOutBaseFileName", "nsegmentout_path");
/*
**	run start and end times
*/
//        decl_control_int_array("start_time", 6, start_date);
//        decl_control_int_array("end_time", 6, end_date);
//        decl_control_int_array("modflow_time_zero", 6, modflow0_date);

/*
**	flag for initializing vars from file
*/
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("init_vars_from_file", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("save_vars_to_file", 1, lval);

/*
**	initial delta-t - hours
*/
//        fval = (float *)umalloc (sizeof (float));
//		fval[0] = 24.0;
//        decl_control_float_array ("initial_deltat", 1, fval);

/*
**	stats analysis
*/

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("statsON_OFF", 1, lval);
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("nstatVars", 1, lval);

/*
**	animation output
*/
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("aniOutON_OFF", 1, lval);
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("naniOutVars", 1, lval);

/*
**	map output
*/
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("mapOutON_OFF", 1, lval);
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("nmapOutVars", 1, lval);

/*
**	nhru_summary
*/
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("nhruOutON_OFF", 1, lval);
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("nhruOutVars", 1, lval);
//		lval = (long *)umalloc(sizeof (long));
//		lval[0] = 1;
//		decl_control_int_array("nhruOut_freq", 1, lval);
//		lval[0] = 1;
//		decl_control_int_array("nhruOut_format", 1, lval);

//		lval[0] = 1;
//		decl_control_int_array("prms_warmup", 1, lval);


		/*
		**	nsub_summary
		*/
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 0;
//		decl_control_int_array("nsubOutON_OFF", 1, lval);
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 0;
//		decl_control_int_array("nsubOutVars", 1, lval);
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 1;
//		decl_control_int_array("nsubOut_freq", 1, lval);
//		lval[0] = 1;
//		decl_control_int_array("nsubOut_format", 1, lval);

		/*
		**	basin_summary
		*/
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 0;
//		decl_control_int_array("basinOutON_OFF", 1, lval);
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 0;
//		decl_control_int_array("basinOutVars", 1, lval);
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 1;
//		decl_control_int_array("basinOut_freq", 1, lval);

		/*
		**	nsegment_summary
		*/
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 0;
//		decl_control_int_array("nsegmentOutON_OFF", 1, lval);
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 0;
//		decl_control_int_array("nsegmentOutVars", 1, lval);
//		lval = (long *)umalloc(sizeof(long));
//		lval[0] = 1;
//		decl_control_int_array("nsegmentOut_freq", 1, lval);
//		lval[0] = 1;
//		decl_control_int_array("nsegmentOut_format", 1, lval);

/*
**	graphics display
*/
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("ndispGraphs", 1, lval);

//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 50;
//        decl_control_int_array ("dispGraphsBuffSize", 1, lval);

// CSV output
//        lval = (long *)umalloc (sizeof (long));
//		lval[0] = 0;
//        decl_control_int_array ("csvON_OFF", 1, lval);

  } // setup

  // | FUNCTION     : add_control
  // | COMMENT		: This allocates a control structure and adds it to the
  // |                control DB.  It also allocates the space for the variables.
  // | RETURN VALUE : None
//CONTROL *add_control (char *key, long type, long size) {
//   CONTROL *cp;

/*
**	check that key does not already exist
*/

//   if (control_addr (key)) {
//      (void)fprintf (stderr,
//         "ERROR - add_control - key '%s' already exists.\n", key);
//      exit(1);
//   }
// printf ("adding control parameter - key: %s type: %ld size: %ld\n", key, type, size);

/*
**  allocate space for a structure, and store pointer in controls
**  allocate space, and store control variable properties
*/
//   cp = (CONTROL *) umalloc (sizeof(CONTROL));
//   ADD_to_list (cont_db, (void *)cp);

//   cp->key = strdup (key);
//   cp->size = size;
//   cp->type = type;
//   cp->set_in_file = 0;

//   if (type == M_STRING) {
//      cp->start_ptr = (char *)umalloc (sizeof (char *) * size);
   
//   } else if (type == M_LONG) {
//      cp->start_ptr = (char *)umalloc (sizeof (long) * size);

//   } else if (type == M_FLOAT) {
//	   cp->start_ptr = (char *)umalloc (sizeof (float) * size);

//   } else if (type == M_DOUBLE) {
//	   cp->start_ptr = (char *)umalloc (sizeof (double) * size);

//   } else {
//      (void)fprintf (stderr,
//         "ERROR - add_control - key '%s' don't know what type code %ld is.\n", key, type);
//      exit(1);
//   }

//   return cp;
//}

  // TODO: valstr's C type was (void *); not sure that Chapel string
  // will work
  proc decl_control(key: string, typ: int, size: int, valstr: string) {
    var cp: ControlType;

    // check that key does not already exist

    if (addr(key)) then {
      stderr.write("ERROR - decl_control - key '%s' already exists.\n", key);
      exit(1);
    }

    // allocate space for a structure, and store pointer in controls
    // allocate space, and store control variable properties

//   cp = (CONTROL *) umalloc (sizeof(CONTROL));
//   ADD_to_list (cont_db, (void *)cp);

//   cp->key = key;
//   cp->size = size;
//   cp->type = type;
//   cp->start_ptr = (char *)valstr;
//   cp->set_in_file = 0;

  }

  proc decl_control_string(key: string, valstr: string) {
    //   char **cp;

    //   cp = (char **)umalloc (sizeof (char *) * 1);
    //   *cp = strdup (valstr);
    //   decl_control (strdup (key), M_STRING, 1, cp);
  }

//void decl_control_string_array (char *key, long size, char *valstr) {
//   char **cp;
//   int i;

//   cp = (char **)umalloc (sizeof (char *) * size);
//   for (i = 0; i < size; i++) {
//      cp[i] = strdup (valstr);
//   }

//   decl_control (strdup (key), M_STRING, size, cp);
//}

  proc decl_control_int_array(key: string, size: int, valstr: int) {
    var lp: int;
    var i: int;

//   lp = (long *)umalloc (sizeof (long) * size);
//   for (i = 0; i < size; i++) {
//      lp[i] = valstr[i];
//  }

//   decl_control (strdup (key), M_LONG, size, lp);
  }

//void decl_control_float_array (char *key, long size, float *valstr) {
//   float *fp;
//   int i;

//   fp = (float *)umalloc (sizeof (float) * size);
//   for (i = 0; i < size; i++) {
//      fp[i] = (float)(valstr[i]);
//   }

//   decl_control (strdup (key), M_FLOAT, size, fp);
//}

//void decl_control_double_array (char *key, long size, double *valstr) {
//   double *fp;
//   int i;

//   fp = (double *)umalloc (sizeof (double) * size);
//   for (i = 0; i < size; i++) {
//      fp[i] = (double)(valstr[i]);
//   }

//   decl_control (strdup (key), M_DOUBLE, size, fp);
//}

/*--------------------------------------------------------------------*\
 | FUNCTION     : decl_control_
 | COMMENT		: decl_control_() is called from Fortran, sorts out args
 |                 and calls decl_control()
 | PARAMETERS   :
 | RETURN VALUE :
 | RESTRICTIONS :
\*--------------------------------------------------------------------*/
//void decl_control_ (char *ckey, ftnint *ctype, ftnint *csize, void *value, ftnlen klen) {
//	char *key;
//	long type, size;

  /*
   * copy ctype and csize to local long int
   */
//	type = *ctype;
//	size = *csize;

  /*
   * copy args to new strings, and terminate correctly
   */
//	key = (char *) umalloc((unsigned int)(klen + 1));
//	strncpy(key, ckey, (int)klen);
//	key[klen] = '\0';

//	decl_control(key, type, size, value);
//	return;
//}

} // Control

/*+
 * United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION :
 * COMMENT  :
 *
 *  $Id$
 *
-*/

/**1************* SWITCH FOR DEFINITION AND DECLARATION ***************/
#ifndef MSYS_PROTO_H
#define MSYS_PROTO_H

/**5**************** DECLARATION EXPORTED FUNCTIONS *******************/

/***  mmf.c  **************************************************/
extern long setdims_ (void);
extern long call_modules_ (char *, int);

/***  get_elem_add.c  **************************************************/
#undef EXTERN
#ifdef GET_ELEM_ADD_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int CheckIndices (char *, char *, int);
EXTERN char *GetElemAddress (char *, char *, int);

/***  oprint.c  **************************************************/
#undef EXTERN
#ifdef OPRINT_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void opstr_ (char *, ftnlen);
EXTERN void opstr (char *);
//EXTERN void opint4_ (char *, ftnint *, ftnint *, ftnlen);
//EXTERN void oplong (char *, long *, long);
//EXTERN void opreal_ (char *, float *, ftnint *, ftnlen);
//EXTERN void opfloat (char *, float *, long);
//EXTERN void opdble_ (char *, double *, ftnint *, ftnlen);
//EXTERN void opdble (char *, double *, long);

///***  rosopt.c  **************************************************/
//#undef EXTERN
//#ifdef ROSOPT_C
//#define EXTERN
//#else
//#define EXTERN extern
//#endif
//
//EXTERN char *rosopt (ROSEN_DATA *, float[], float[]);

///***  opinit.c  **************************************************/
//#undef EXTERN
//#ifdef OPINIT_C
//#define EXTERN
//#else
//#define EXTERN extern
//#endif
//
//EXTERN char *opinit (float *, float *, int *, ROSEN_DATA *);

/***  bdry.c  **************************************************/
#undef EXTERN
#ifdef BDRY_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int bdry (float *, int *, float *, float *, int *, int *, float *);

/***  coropt.c  **************************************************/
#undef EXTERN
#ifdef COROPT_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int coropt (int *, float *, float *, int *);

/***  tcale.c  **************************************************/
#undef EXTERN
#ifdef TCALE_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int tcale (int *, float *, float *, float *, float *, int *);

/***  unscal.c  **************************************************/
#undef EXTERN
#ifdef UNSCAL_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int unscal (int *, float *, float *, float *, float *, int *);

/***  parse_args.c  **************************************************/
#undef EXTERN
#ifdef PARSE_ARGS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void parse_args (int, char **, int *, char **, char **, int);

/***  read_datainfo.c  **************************************************/
#undef EXTERN
#ifdef READ_DATAINFO_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN char *read_datainfo (FILE_DATA *);

EXTERN char *DATA_read_init (void);
EXTERN char *DATA_check_start (void);
EXTERN void DATA_close (void);
EXTERN int control_var_size (char *);
EXTERN FILE_DATA *FILE_with_next_ts (void);
EXTERN char *EXTRACT_time (FILE_DATA *);
EXTERN int CHECK_data (int, FILE_DATA *);
EXTERN void DATA_find_end (DATETIME *, DATETIME *);
EXTERN char *READ_data_info (void);

/***  setup_cont.c  **************************************************/
#undef EXTERN
#ifdef SETUP_CONT_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void setup_cont (void);

/***  stats.c  **************************************************/
#undef EXTERN
#ifdef STATS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int stats (void);

/***  write_vstats.c  **************************************************/
#undef EXTERN
#ifdef WRITE_VSTATS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void write_vstats (FILE *);

/***  julconvert.c  **************************************************/
#undef EXTERN
#ifdef JULCONVERT_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN double getjulday(int, int, int, int, int, double);
EXTERN int dayofweek(double);
EXTERN long isleap_ (ftnint *);
EXTERN int isleap (int);

/***  build_lists.c  **************************************************/
#undef EXTERN
#ifdef BUILD_LISTS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN LIST *ALLOC_list (char *, int, int);
EXTERN void RESIZE_list (LIST *, int);
EXTERN void DELETE_list (LIST *);
EXTERN void ADD_to_list (LIST *, void *);

/***  sensitivity.c  **************************************************/
#undef EXTERN
#ifdef SENSITIVITY_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN char *PRMS_sens (void);
EXTERN int IN_obj_period (int, int, int);

/***  declmodule.c    **************************************************/
EXTERN long declmodule (char *, char *, char *);

/***  decl_control.c  **************************************************/
#undef EXTERN
#ifdef DECL_CONTROL_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN long declparam_u_ (char *, char *, char *, char *, char *,
	char *, char *, char *, char *, char *, char *, long *,
       	ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen);
EXTERN long declparam_u (char *, char *, char *, char *, char *,
	char *, char *, char *, char *, char *, char *, long *);

EXTERN long declparam_p_ (char *, char *, char *, char *, char *,
	char *, char *, char *, char *, char *, char *, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen);
EXTERN long declparam_p (char *, char *, char *, char *, char *,
	char *, char *, char *, char *, char *, char *);

EXTERN long declpri_ (char *, ftnint *, char *, char *, ftnlen, ftnlen);
EXTERN long declpri (char *, long, char *, char *);

/***  dim_addr.c  **************************************************/
#undef EXTERN
#ifdef DIM_ADDR_C
#define EXTERN
#else
#define EXTERN extern
#endif

/***  getdimname.c  **************************************************/
#undef EXTERN
#ifdef GETDIMNAME_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void getdimname_ (char *, ftnint *, char *, ftnlen, ftnlen);
EXTERN void getdimname (char *, long, char *, int);
EXTERN void getdimdesc_ (char *, ftnint *, char *, ftnlen, ftnlen);
EXTERN void getdimdesc (char *, long, char *, int);

/***  getparam.c  **************************************************/
#undef EXTERN
#ifdef GETPARAM_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN long getparam_ (char *, char *, ftnint *, char *, double *, ftnlen, ftnlen, ftnlen);
EXTERN long getparam (char *, char *, int, char *, double *);
EXTERN long getdatainfo_ (char *, ftnlen);
EXTERN long getdatainfo (char *, ftnlen);
EXTERN long getdataname_ (char *, char *, ftnlen, ftnlen);
EXTERN long getdataname (char *, int, char *);
EXTERN long getoutdirfile_ (char *, char *, ftnlen, ftnlen);
EXTERN long getoutdirfile (char *, int, char *);
EXTERN long getuserdirfile_ (char *, char *, ftnlen, ftnlen);
EXTERN long getuserdirfile (char *, int, char *);

/***  getvar.c  **************************************************/
#undef EXTERN
#ifdef GETVAR_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN long getvar_ (char *, char *, ftnint *, char *, double *,
	ftnlen, ftnlen, ftnlen);
EXTERN long getvar (char *, char *, long, char *, double *);

/***  load_param.c  **************************************************/
#undef EXTERN
#ifdef LOAD_PARAM_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN long load_param (PARAM *);

/***  param_addr.c  **************************************************/
#undef EXTERN
#ifdef PARAM_ADDR_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN PARAM *param_addr (char *);

/***  putvar.c  **************************************************/
#undef EXTERN
#ifdef PUTVAR_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN long putvar_ (char *, char *, ftnint *, char *, double *value,
	     ftnlen, ftnlen, ftnlen);
EXTERN long putvar (char *, char *, long, char *, double *);

/***  read_vars.c  **************************************************/
#undef EXTERN
#ifdef READ_VARS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int read_vars (char *);

/***  readvar.c  **************************************************/
#undef EXTERN
#ifdef READVAR_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN long readvar_ (char *, char *, ftnlen, ftnlen);
EXTERN long readvar (char *, char *);

/***  reset_dim.c  **************************************************/
#undef EXTERN
#ifdef RESET_DIM_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void reset_dim (DIMEN *, long);

/***  save_control.c  **************************************************/
#undef EXTERN
#ifdef SAVE_CONTROL_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void save_control (char *);

/***  save_vars.c  **************************************************/
#undef EXTERN
#ifdef SAVE_VARS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int save_vars (char *);

/***  sort_params.c  **************************************************/
#undef EXTERN
#ifdef SORT_PARAMS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void sort_params (void);

/***  sort_vars.c  **************************************************/
#undef EXTERN
#ifdef SORT_VARS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void sort_vars (void);

/***  str_to_vals.c  **************************************************/
#undef EXTERN
#ifdef STR_TO_VALS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN long str_to_vals (char *, long, long, char *);

/***  timing.c  **************************************************/
#undef EXTERN
#ifdef TIMING_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void dattim_ (char *, ftnint *, ftnlen);
EXTERN void dattim (char *, long *);
EXTERN long julian_ (char *, char *, ftnlen, ftnlen);
EXTERN long julian (char *, char *);
EXTERN double deltim (void);
EXTERN double delnex (void);
EXTERN long getstep_ (void);
EXTERN long getstep (void);
EXTERN double djulian_ (char *, char *, ftnlen, ftnlen);
EXTERN double djulian (char *, char *);

/***  var_addr.c  **************************************************/
#undef EXTERN
#ifdef VAR_ADDR_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN PUBVAR *var_addr (char *);

/***  esp_batch_run.c  **************************************************/
#undef EXTERN
#ifdef ESP_BATCH_RUN_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN char *ESP_batch_run (void);

/***  rosenbrock_batch_run.c  **************************************************/
#undef EXTERN
#ifdef ROSENBROCK_BATCH_RUN_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void ROSENBROCK_batch_run (void);

/***  umalloc_etc.c  **************************************************/
#undef EXTERN
#ifdef UMALLOC_ETC_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN char *umalloc (unsigned);
EXTERN char *urealloc (char *, unsigned);
EXTERN char *ucalloc (unsigned, unsigned);
EXTERN void ufree (char *);

/***  julday.c  **************************************************/
#undef EXTERN
#ifdef JULDAY_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int julday (DATETIME *);

/***  matinv.c  **************************************************/
#undef EXTERN
#ifdef MATINV_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int matinv (float *, float *, int *, int *);

/***  matind.c  **************************************************/
#undef EXTERN
#ifdef MATIND_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int matind (double *, double *, int *);

/***  snort.c  **************************************************/
#undef EXTERN
#ifdef SNORT_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int snort (float *, int *, int *, int *);

/***  print_model_info.c  **************************************************/
#undef EXTERN
#ifdef PRINT_MODEL_INFO_C
#define EXTERN
#else
#define EXTERN extern
#endif

#endif

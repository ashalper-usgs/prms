/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 */

#ifndef MMS_GLOBAL_H
#define MMS_GLOBAL_H

/*
 * for all functions except main
 */

extern int max_data_ln_len;
extern char *MAltContFile;
extern long Mdebuglevel;
extern char *model_name;
extern char *executable_model;
extern int batch_run_mode;
extern int run_period_of_record;
extern int print_mode;
extern int runtime_graph_on;
extern int preprocess_on;
extern LIST *cont_db;
extern LIST *dim_db;
extern LIST *module_db;
extern MODULE_DATA *current_module;
extern PUBVAR **Mvarbase;
extern long Mnvars;
extern PARAM **Mparambase;
extern long Mnparams;
extern READCHECK **Mcheckbase;
extern long Mnreads;
extern DATETIME *Mstrttime;
extern DATETIME *Mendtime;
extern DATETIME *Mnowtime;
extern DATETIME *Mnexttime;
extern char *Mparaminfo;
extern char *Mdatainfo;
extern PARAM **unsort_params;
extern FILE_DATA   **fd;
extern long Mnsteps;
extern double Mprevjt;
extern char *Minpptr;
extern int  M_stop_run;
extern STAT_LIST_TYPE *Mfirst_stat_list;
extern long ParamBaseIsDirty;
extern int max_vars;
extern int max_params;
extern int max_read_vars;
extern int max_dims;
extern int max_controls;

#endif /* MMS_GLOBAL_H */

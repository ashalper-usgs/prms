LIST *cont_db;
LIST *dim_db;
int max_vars;
PUBVAR **Mvarbase = NULL;   /* pointer to public variables database */
long Mnvars = 0;	    /* no of public variables in database */
PARAM **Mparambase = NULL;  /* pointer to parameter data base */
long Mnparams = 0;	    /* no of params in data base */
READCHECK **Mcheckbase = NULL;	/* pointer to read check data base */
long Mnreads = 0;	  /* max no. of calls to be made by readvar */
DATETIME *Mstrttime = NULL;	/* pointer to start time structure */
DATETIME *Mendtime = NULL;	/* pointer to end time structure */
DATETIME *Mnowtime = NULL; /* pointer to current data time structure */
DATETIME *Mnexttime = NULL;  /* pointer to next data time structure */
char *Mparaminfo = NULL;     /* pointer to param information string */
char *Mdatainfo = NULL;	     /* pointer to data information string */
long Mdebuglevel = 0;	     /* the current debug level */
int max_params;
int max_read_vars;

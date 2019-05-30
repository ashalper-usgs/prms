long read_line (long, double *, double*);

char *DATA_read_init (void);

char *READ_data_info (void);

char *DATA_check_start (void);

void DATA_close (void);

int control_var_size (char *);

FILE_DATA * FILE_with_next_ts (void);

char * EXTRACT_time (FILE_DATA *);

int CHECK_data (int, FILE_DATA *);

void DATA_find_end (DATETIME *, DATETIME *);

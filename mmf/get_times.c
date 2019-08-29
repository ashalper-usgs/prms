/*+
 * United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : get_times
 * COMMENT  : get start and end times from control data base
-*/

#define GET_TIMES_C
#include <stdio.h>
#include "mms.h"
#include "control_var.h"
#include "get_times.h"

void get_times (LIST *cont_db) {
  long *datetime;
  float *newvalue;

  datetime = (long *) control_var(cont_db, "start_time");
  Mstrttime->year = datetime[0];
  Mstrttime->month = datetime[1];
  Mstrttime->day = datetime[2];
  Mstrttime->hour = datetime[3];
  Mstrttime->min = datetime[4];
  Mstrttime->sec = datetime[5];

  datetime = (long *) control_var(cont_db, "end_time");
  Mendtime->year = datetime[0];
  Mendtime->month = datetime[1];
  Mendtime->day = datetime[2];
  Mendtime->hour = datetime[3];
  Mendtime->min = datetime[4];
  Mendtime->sec = datetime[5];

  /* compute Julian day for start and end  - this fills in the Julian date
     parts of the datetime data structure */

  julday(Mstrttime);
  julday(Mendtime);

  newvalue = (float *) control_var(cont_db, "initial_deltat");
  Mdeltat = (double)(*newvalue / 24.0);
  Mdeltanext = (double)(*newvalue / 24.0);
}

/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : get_times
 * COMMENT  : get start and end times from control database
 */

#include "defs.h"
#include "structs.h"
#include "globals.h"
#include "control_var.h"
#include "julday.h"
#include "get_times.h"

/* in prms.c */
extern DATETIME *Mstrttime;
extern DATETIME *Mendtime;

/*--------------------------------------------------------------------*\
  | FUNCTION     : get_times
\*--------------------------------------------------------------------*/
void get_times (double *Mdeltat, double *Mdeltanext) {
  long *datetime;
  float *newvalue;

  datetime = (long *) control_var("start_time");
  Mstrttime->year = datetime[0];
  Mstrttime->month = datetime[1];
  Mstrttime->day = datetime[2];
  Mstrttime->hour = datetime[3];
  Mstrttime->min = datetime[4];
  Mstrttime->sec = datetime[5];

  datetime = (long *) control_var("end_time");
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

  newvalue = (float *) control_var("initial_deltat");
  *Mdeltat = (double)(*newvalue / 24.0);
  *Mdeltanext = (double)(*newvalue / 24.0);
}

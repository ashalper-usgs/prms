/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : julday()
 * COMMENT  : computes Julian day, puts it into the jd slot in the
 *            datetime structure
 */

#include <math.h>
#include "structs.h"
#include "julday.h"

#define IGREG (15+31L*(10+12L*1582))

/*--------------------------------------------------------------------*\
 | FUNCTION     : julday
\*--------------------------------------------------------------------*/
int julday (DATETIME *datetime) {

  long jul;
  int ja,jy,jm, iyyy, mm, id;

  iyyy = datetime->year;
  mm = datetime->month;
  id = datetime->day;

  if (iyyy == 0) {
    (void)fprintf(stderr, "JULDAY: there is no year zero.");
    return(1);
  }

  if (iyyy < 0) ++iyyy;
  if (mm > 2) {
    jy=iyyy;
    jm=mm+1;
  } else {
    jy=iyyy-1;
    jm=mm+13;
  }
  jul = (long) (floor(365.25*jy)+floor(30.6001*jm)+id+1720995);
  if (id+31L*(mm+12L*iyyy) >= IGREG) {
    ja=0.01*jy;
    jul += 2-ja+(int) (0.25*ja);
  }
  datetime->jd = jul;
  datetime->jt = (double) jul + (double) datetime->hour / 24.0
                              + (double) datetime->min / 1440.0
			      + (double) datetime->sec / 86400.0;

  return (0);
}
#undef IGREG

/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : write_vstats
 * COMMENT  : saves values of stat variables into a temporary file.
 *            The temporary file was open in user_input
 */

#include <stdio.h>
#include "structs.h"
#include "globals.h"
#include "defs.h"
#include "write_vstats.h"

/* in prms.c */
extern DATETIME *Mnowtime;

/*--------------------------------------------------------------------*\
 | FUNCTION     : write_vstats
 | RETURN VALUE : None.
\*--------------------------------------------------------------------*/
void write_vstats (FILE *statvar_file, long Mnsteps) { 

  STAT_LIST_TYPE *stat_list;

  /*
   * writes first record number, date and time info
   */

  (void)fprintf(statvar_file, "%ld %ld %ld %ld %ld %ld %ld ",
	  Mnsteps, Mnowtime->year,
	  Mnowtime->month, Mnowtime->day, Mnowtime->hour,
	  Mnowtime->min, Mnowtime->sec);

  /*
   * Initializes linked list to first pointer
   */

  stat_list = Mfirst_stat_list;

  /*
   * The list is NULL-terminated
   */

  while (stat_list)  {
    
    /*
     * Gets variable value
     */

    switch (stat_list->type) {

    case M_FLOAT:

      (void)fprintf(statvar_file,"%f ", *(float *)stat_list->value);
      break;

    case M_DOUBLE:

      (void)fprintf(statvar_file,"%lf ", *(double *)stat_list->value);
      break;

    case M_LONG:
	(void)fprintf(statvar_file,"%d ", *(int *)stat_list->value);
      break;

    }

    /*
     * Updates pointer
     */

    stat_list = stat_list->next;

  }

  (void)fprintf(statvar_file,"\n");

}

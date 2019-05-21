/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : batch_run
 * COMMENT  : runs the MMS time loop
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "structs.h"
#include "globals.h"

extern int call_modules (char *);
extern char *single_run_pre_init (void);
extern char *single_run_post_init (void);
extern char *single_run_pre_run (void);
extern char *single_run_post_run (void);
extern char *single_run_post_cleanup (void);

/*--------------------------------------------------------------------*\
 | FUNCTION     : BATCH_run
 | COMMENT      :
 | PARAMETERS   : None
 | RETURN VALUE : char * - error message if there is one.
 | RESTRICTIONS : None
\*--------------------------------------------------------------------*/
int BATCH_run (void) {
   char *ret;
   long endofdata = 0;

   ret = single_run_pre_init ();
   if (ret) {
      fprintf (stderr,"%s\n", ret);
      return(1);
   }

   if (call_modules("initialize")) {
      fprintf (stderr, "single_run:  Problem with initializing modules.");
      return(1);
   }

   ret = single_run_post_init ();
   if (ret) return(1);

/*
* perform the main loop
*/

   M_stop_run = 0;
   Mprevjt = -1.0;

   while(!endofdata) {
      if(!(endofdata = read_line ())) {
         ret = single_run_pre_run ();
         if (ret) return(1);

         errno = 0;

         if(call_modules("run")) {
            fprintf (stderr, "Problem while running modules.");
            return(1);
         }

         ret = single_run_post_run ();
         if (ret) return(1);
      }
   }

   ret = single_run_post_cleanup ();
   if (ret) return(1);

/*
* cleanup modules
*/

   if (call_modules("cleanup")) {
       fprintf (stderr, "Problem with module cleanup.");
       return(1);
   }

   return(0);
}

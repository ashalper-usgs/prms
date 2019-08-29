/*+
 * United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : graph_single_run
 * COMMENT  : graph routines for mms run
-*/

#define GRAPH_SINGLE_RUN_C
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mms.h"

#include "control_addr.h"
#include "control_array.h"

#include "graph_single_run.h"

#define MAXNUMBEROFGRAPHS 4

long NdispGraphs;
static double zero_time;
PUBVAR **disp_var;
int *disp_ele;
int numDispVars;

int initializeRuntimeGraphs (LIST *cont_db) {
   CONTROL *control;
   int i;
   DATETIME starttime_copy;
   char *cptr, *cptr2;

   if (!runtime_graph_on) return (FALSE);

   starttime_copy.year =Mstrttime->year;
   starttime_copy.month =Mstrttime->month;
   starttime_copy.day = Mstrttime->day;
   starttime_copy.hour =Mstrttime->hour;
   starttime_copy.min =Mstrttime->min;
   starttime_copy.sec =Mstrttime->sec;

   julday(&starttime_copy);

   zero_time = starttime_copy.jt;

/*
** Get the number of display vars
*/
   cptr = strdup ("dispVar_names");
   control = control_addr(cont_db, cptr);
   if (control) {
      numDispVars = control->size;

      disp_var = (PUBVAR **)malloc (sizeof(PUBVAR *) * numDispVars);
      memset (disp_var, 0, sizeof (PUBVAR *) * numDispVars);

      disp_ele = (int *)malloc (sizeof (int) * numDispVars);
      memset (disp_ele, 0, sizeof (int) * numDispVars);

      for (i = 0; i < numDispVars; i++) {
/**
** Get address of each display variable for each graph
**/
         cptr = strdup ("dispVar_names");
	 cptr2 = (char *)control_sarray(cont_db, cptr, i);

         disp_var[i] = var_addr (cptr2);

         cptr = strdup ("dispVar_element");
         disp_ele[i] =  atoi (control_sarray(cont_db, cptr ,i)) - 1;
      }
   } else {
	   numDispVars = 0;
	   disp_var = NULL;
	   disp_ele = NULL;
	   runtime_graph_on = 0;
   }
   return (FALSE);
}

int plotRuntimeGraphValue (void) {
   double xval;
   float yval;
   int i;
   DATETIME nowtime_copy;

   if (!runtime_graph_on) return (FALSE);

   nowtime_copy.year = Mnowtime->year;
   nowtime_copy.month = Mnowtime->month;
   nowtime_copy.day = Mnowtime->day;
   nowtime_copy.hour = Mnowtime->hour;
   nowtime_copy.min = Mnowtime->min;
   nowtime_copy.sec = Mnowtime->sec;

   julday(&nowtime_copy);

   xval = nowtime_copy.jt - zero_time;

   printf ("plotRuntimeGraphValue: xval = %f", xval);

   for (i = 0; i < numDispVars; i++) {
      yval = 0.0;
      switch ((disp_var[i])->type) {
         case M_LONG :
            yval = (float)(*(((long *)((disp_var[i])->value)) + disp_ele[i]));
            break;

         case M_DOUBLE :
            yval = (float)(*(((double *)((disp_var[i])->value)) + disp_ele[i]));
            break;

         case M_FLOAT :
            yval = *(((float *)((disp_var[i])->value)) + disp_ele[i]);
            break;
      }
      printf (" %f", yval);
   }
   printf ("\n");
   fflush (stdout);

   return (FALSE);
}

int closeRuntimeGraphs (void) {
   if (!runtime_graph_on) return (FALSE);

   printf ("closeRuntimeGraph\n");
   return (FALSE);
}

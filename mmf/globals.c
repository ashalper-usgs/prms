/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * COMMENT  : Global variable declarations.
 */

#include "structs.h"

char *Mtypes[] = {"", "long", "float", "double", "string", "", "","", "", ""};
PARAM **unsort_params = NULL;	/* pointer to unsorted parameters */
double Mdeltat = 0.0;		/* the latest time step in hours */
long Mnsteps = 0;		/* the number of steps so far */
double Mdeltanext = 0.0;      /* the latest next time step in hours */

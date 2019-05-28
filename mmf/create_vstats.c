/* United States Geological Survey (USGS)
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : create_vstats
 * COMMENT  : create linked list for stats variables
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "control_var.h"
#include "get_elem_add.h"
#include "umalloc_etc.h"
#include "var_addr.h"
#include "create_vstats.h"

/*--------------------------------------------------------------------*\
  | FUNCTION     : create_vstats
\*--------------------------------------------------------------------*/
void create_vstats (void) {

  long *nstatVars, i;
  char **statVar_names;
  char **statVar_element;
  char *ptr;
  STAT_LIST_TYPE *curr_stat_list;
  PUBVAR *var;

  /*
   * get number of statVars
   */

  nstatVars = (long *) control_var("nstatVars");

  /*
   * get address of statVar names array 
   */
  
  statVar_names = (char **) control_var("statVar_names");
  
  /*
   * get address of statVar element  array 
   */
  
  statVar_element = (char **) control_svar("statVar_element");

  curr_stat_list  = NULL;
  Mfirst_stat_list = NULL;
  for (i = 0; i < *nstatVars; i++) {

    if (curr_stat_list == NULL) {
      curr_stat_list = (STAT_LIST_TYPE *)umalloc(sizeof(STAT_LIST_TYPE));
      curr_stat_list->key = (char *) umalloc(max_data_ln_len * sizeof(char));
      Mfirst_stat_list = curr_stat_list;
    } else {
      curr_stat_list->next =(STAT_LIST_TYPE *)umalloc(sizeof(STAT_LIST_TYPE));
      curr_stat_list->next->key =
	(char *) umalloc(max_data_ln_len * sizeof(char));
      curr_stat_list = curr_stat_list->next;
    }

    (void)strncpy (curr_stat_list->key, statVar_names[i], max_data_ln_len);
    ptr = strchr (curr_stat_list->key, '.');
    if (ptr) *ptr = '\0';

    curr_stat_list->element = statVar_element[i];
    curr_stat_list->value =
      (char *)GetElemAddress (curr_stat_list->key,
			      statVar_element[i], M_VARIABLE);

    if ((var = var_addr (curr_stat_list->key)) == NULL ) {
      (void)fprintf(stderr, "ERROR - create_vstats.\n");
      (void)fprintf(stderr, "Getting var_addr for var '%s'.\n",
		    statVar_names[i]);
      exit(1);
    }
    curr_stat_list->type = var->type;
    curr_stat_list->next = NULL;

  }
}

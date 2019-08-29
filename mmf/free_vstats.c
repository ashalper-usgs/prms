/*+
 * United States Geological Survey
 *
 * PROJECT  : Modular Modeling System (MMS)
 * FUNCTION : free_vstats
 * COMMENT  : free linked list for stats variables
-*/

#define FREE_VSTATS_C
#include <stdio.h>
#include <string.h>
#include "mms.h"
#include "control_var.h"
#include "free_vstats.h"

void free_vstats (LIST *cont_db) {
  long nstatVars;
  STAT_LIST_TYPE *curr_stat_list, *prev_stat_list;

  nstatVars = *control_lvar(cont_db, "nstatVars");

  if (nstatVars > 0) {

    curr_stat_list  = Mfirst_stat_list;

    while (curr_stat_list->next != NULL) {
      	prev_stat_list = curr_stat_list;
		curr_stat_list = prev_stat_list->next;
    }

	Mfirst_stat_list = NULL;
  }
}

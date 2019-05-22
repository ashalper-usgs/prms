#include <stdio.h>
#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "structs.h"
#include "alloc_space.h"

extern LIST *cont_db;

void setup(void)
{
  alloc_space();
}

void teardown(void)
{
  free(cont_db);
}

START_TEST(test_cont_db)
{
  ck_assert(0 < sizeof(*cont_db));
  ck_assert_str_eq(cont_db->name, "Control Data Base");
  ck_assert_int_eq(cont_db->size, 100);
  ck_assert_int_eq(cont_db->count, 0);
}
END_TEST

Suite * alloc_space_suite(void)
{
    Suite *s;

    TCase *tc_core;
    TCase *tc_limits;

    s = suite_create("alloc_space");

    // Core test case
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_cont_db);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = alloc_space_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

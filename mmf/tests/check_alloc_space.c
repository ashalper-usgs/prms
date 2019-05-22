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
  // money_free(five_dollars);
}

START_TEST(test_default)
{
  // ck_assert_int_eq(1, 1);
  // ck_assert_str_eq(money_currency(five_dollars), "USD");
  ck_abort_msg(cont_db);
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
    tcase_add_test(tc_core, test_default);
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

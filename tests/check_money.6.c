#include <stdlib.h>
#include <check.h>
#include "../src/money.h"

START_TEST (test_money_create)
{
  Money *m;
  m = money_create (5, "USD");
  ck_assert_int_eq (money_amount (m), 5);
  ck_assert_str_eq (money_currency (m), "USD");
  money_free (m);
}
END_TEST

START_TEST (test_money_create_neg)
{
  Money *m = money_create (-1, "USD");
  ck_assert_msg (m == NULL,
	       "NULL should be returned on attempt to create with "
	       "a negative amount");
}
END_TEST

START_TEST (test_money_create_zero)
{
  Money *m = money_create (0, "USD");
  if(money_amount (m) != 0)
  {
    ck_abort_msg("Zero is a valid amount of money");
  }
}
END_TEST

Suite *
money_suite (void)
{
  Suite *s = suite_create ("Money");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_money_create);
  suite_add_tcase (s, tc_core);

  /* Limits test case */
  TCase *tc_limits = tcase_create ("Limits");
  tcase_add_test (tc_limits, test_money_create_neg);
  tcase_add_test (tc_limits, test_money_create_zero);
  suite_add_tcase (s, tc_limits);

  return s;
}

int
main (void)
{
  int number_failed;
  Suite *s = money_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

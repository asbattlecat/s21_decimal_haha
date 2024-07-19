#include "s21_decimal.h"

#include <check.h>
#include <stdio.h>

START_TEST(test_add) {
  {
    int num1, num2, sum_int, res_int;
    s21_decimal a, b, res_dec;

    num1 = 52;
    num2 = 32;
    sum_int = 84;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);
    ck_assert_int_eq(s21_add(a, b, &res_dec), 0);

    num1 = 1200;
    num2 = 3200;
    sum_int = 4400;
    s21_from_int_to_decimal(num1, &a);
    s21_from_int_to_decimal(num2, &b);
    s21_add(a, b, &res_dec);
    s21_from_decimal_to_int(res_dec, &res_int);
    ck_assert_int_eq(res_int, sum_int);
  }
}
END_TEST

Suite* suite_s21_decimal(void) {
  Suite* s;
  TCase* tc_tests;

  s = suite_create("arithmetic test");
  tc_tests = tcase_create("s21_decimal");

  tcase_add_test(tc_tests, test_add);
  suite_add_tcase(s, tc_tests);
  return s;
}

int main(void) {
  Suite* s = suite_s21_decimal();
  SRunner* runner = srunner_create(s);

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? 0 : 1;
}
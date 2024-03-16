#include "s21_math_test.h"

#define actual(x) s21_isinteger(x)

START_TEST(s21_isineger_test_int) {
  const bool expected = true;
  const double step = 1.;
  double start = -1.e+3;
  double end = +1.e+3;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_int_eq(actual(start), expected);
    start += step;
  }
}
END_TEST

START_TEST(s21_isineger_test_not_int) {
  const bool expected = false;
  const double step = 1.e-3;
  double start = -1.e-3;
  double end = 0;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_int_eq(actual(start), expected);
    start += step;
  }
}
END_TEST

static double edge_vals[] = {1e-9, -0, 0, DBL_MIN, 7.345e-29, -0.567, FLT_MAX};
static int edge_expected[] = {false, true, true, false, false, false, true};

START_TEST(s21_isineger_test_edge) {
  double val = edge_vals[_i];
  bool extected = edge_expected[_i];
  ck_assert_int_eq(actual(val), extected);
}
END_TEST

Suite *suite_s21_isinteger() {
  Suite *suite = suite_create("suite_s21_isinteger");

  TCase *int_case = tcase_create("s21_isinteger_int");
  tcase_add_test(int_case, s21_isineger_test_int);
  suite_add_tcase(suite, int_case);

  TCase *not_int_case = tcase_create("s21_isinteger_not_int");
  tcase_add_test(not_int_case, s21_isineger_test_not_int);
  suite_add_tcase(suite, not_int_case);

  TCase *edge_case = tcase_create("s21_isinteger_edge_vals");
  tcase_add_test(edge_case, s21_isineger_test_edge);
  suite_add_tcase(suite, edge_case);

  return suite;
}

#include "s21_math_test.h"

#define actual(x) s21_log(x)
#define expected(x) logl(x)

START_TEST(log_test_normal_loop) {
  const double step = 1;
  double start = 1;
  double end = 350;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(expected(start), actual(start), S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

static double edge_vals[] = {1.234e-43, 1, 10.e+17, DBL_MAX, DBL_MIN};

START_TEST(log_test_edge) {
  double val = edge_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

START_TEST(log_test_edge_close_zero) {
  const double step = 1.e-6;
  double start = 1.e-6;
  double end = 1.e-4;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(expected(start), actual(start), S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

START_TEST(log_test_edge_huge) {
  double step = .5E+12;
  double start = 1.9E+16;
  double end = 1.91E+16;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(expected(start), actual(start), S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

static double anomaly_vals[] = {NAN, -NAN,    -10,      -1.e-9,   1.,
                                0.0, 0. / 0., INFINITY, -INFINITY};

START_TEST(log_test_anomaly) {
  double val = anomaly_vals[_i];
  if (isnan(val)) {
    ck_assert_int_eq(isnan(actual(val)), isnan(expected(val)));
  } else if (val < 0) {
    ck_assert_int_eq(isnan(actual(val)), isnan(expected(val)));
  } else if (val == 0) {
    int actual_test_res = (isinf(actual(val)) && actual(val) < 0);
    int expected_test_res = (isinf(expected(val)) && expected(val) < 0);
    ck_assert_int_eq(actual_test_res, expected_test_res);
  } else if (isinf(val)) {
    ck_assert_int_eq(isinf(actual(val)), isinf(expected(val)));
  } else {
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
  }
}
END_TEST

Suite *suite_s21_log() {
  Suite *suite = suite_create("suite_s21_log");

  TCase *normal_case_loop = tcase_create("s21_log_normal_vals");
  tcase_add_test(normal_case_loop, log_test_normal_loop);
  suite_add_tcase(suite, normal_case_loop);

  TCase *edge_case = tcase_create("s21_log_edge_vals");
  tcase_add_loop_test(edge_case, log_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *edge_case_close_zero = tcase_create("s21_log_edge_vals_close_zero");
  tcase_add_test(edge_case_close_zero, log_test_edge_close_zero);
  suite_add_tcase(suite, edge_case_close_zero);

  TCase *edge_case_huge = tcase_create("s21_log_edge_vals_huge");
  tcase_add_test(edge_case_huge, log_test_edge_huge);
  suite_add_tcase(suite, edge_case_huge);

  TCase *anomaly_case = tcase_create("s21_log_anomaly_vals");
  tcase_add_loop_test(anomaly_case, log_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}

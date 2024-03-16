#include "s21_math_test.h"

#define actual(x) s21_atan(x)
#define expected(x) atanl(x)

START_TEST(atan_test_normal_loop) {
  const double step = 1.e-1;
  double start = -20.;
  double end = 20.;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(actual(start), expected(start), S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

static double edge_vals[] = {1e-9,      -0,     0,       FLT_MIN,
                             7.345e-29, -0.567, FLT_MAX, -FLT_MAX};

START_TEST(atan_test_edge) {
  double val = edge_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

START_TEST(atan_test_edge_close_1) {
  const double step = 1.e-6;
  double start = 0.999998;
  double end = 1.;

  while ((end - start) > S21_EPS_DEFAULT) {
    ck_assert_ldouble_eq_tol(actual(start), expected(start), S21_EPS_DEFAULT);
    start += step;
  }
}
END_TEST

START_TEST(atan_test_edge_close_minus_1) {
  const double step = 1.e-6;
  double start = -1.;
  double end = -0.999998;

  while ((end - start) > S21_EPS_DEFAULT) {
    ck_assert_ldouble_eq_tol(actual(start), expected(start), S21_EPS_DEFAULT);
    start += step;
  }
}
END_TEST

static double anomaly_vals[] = {NAN,     -NAN,     -0.0,     -1 / 0.0,
                                0. / 0., INFINITY, -INFINITY};

START_TEST(atan_test_anomaly) {
  double val = anomaly_vals[_i];
  if (isnan(val)) {
    ck_assert_int_eq(isnan(actual(val)), isnan(expected(val)));
  } else if (isinf(val)) {
    if (val > 0)
      ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
    if (val < 0)
      ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
  } else {
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
  }
}
END_TEST

Suite *suite_s21_atan() {
  Suite *suite = suite_create("suite_s21_atan");

  TCase *normal_case_loop = tcase_create("s21_atan_normal_vals_loop");
  tcase_add_test(normal_case_loop, atan_test_normal_loop);
  suite_add_tcase(suite, normal_case_loop);

  TCase *edge_case = tcase_create("s21_atan_edge_vals");
  tcase_add_loop_test(edge_case, atan_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *edge_case_close_1 = tcase_create("s21_atan_edge_close_1");
  tcase_add_test(edge_case_close_1, atan_test_edge_close_1);
  suite_add_tcase(suite, edge_case_close_1);

  TCase *edge_case_close_minus_1 = tcase_create("s21_atan_edge_close_minus_1");
  tcase_add_test(edge_case_close_minus_1, atan_test_edge_close_minus_1);
  suite_add_tcase(suite, edge_case_close_minus_1);

  TCase *anomaly_case = tcase_create("s21_atan_anomaly_vals");
  tcase_add_loop_test(anomaly_case, atan_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}
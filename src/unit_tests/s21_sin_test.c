#include "s21_math_test.h"

#define actual(x) s21_sin(x)
#define expected(x) sinl(x)

static long double normal_vals[] = {
    0.,           S21_PI,      S21_PI / 2.,        2. * S21_PI,
    -S21_PI / 2., S21_PI / 4., (S21_PI * 5.) / 6., S21_PI / 3.};

START_TEST(sin_test_normal) {
  double val = normal_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_DEFAULT);
}
END_TEST

START_TEST(sin_test_normal_loop) {
  double step = 0.001;
  double start = -10.;
  double end = 10.;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(actual(start), expected(start), S21_EPS_DEFAULT);
    start += step;
  }
}
END_TEST

START_TEST(sin_test_normal_PI_fract) {
  int i = _i;
  if (i != 0) {
    ck_assert_ldouble_eq_tol(actual(S21_PI / i), expected(S21_PI / i),
                             S21_EPS_DEFAULT);
  } else {
    ck_assert_ldouble_nan(actual(S21_PI / i));
  }
}
END_TEST

START_TEST(sin_test_normal_PI_whole) {
  int i = _i;
  ck_assert_ldouble_eq_tol(actual(S21_PI * i), expected(S21_PI * i),
                           S21_EPS_DEFAULT);
}
END_TEST

static double edge_vals[] = {4754754453, -4754754453,        FLT_MIN, -0,
                             0,          246524626.3242344,  DBL_MIN, 1.e-9,
                             7.345e-29,  0.12345678975434534};

START_TEST(sin_test_edge) {
  double val = edge_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_DEFAULT);
}
END_TEST

static double anomaly_vals[] = {NAN, -0.0, 0 / -0.0, INFINITY};

START_TEST(sin_test_anomaly) {
  double val = anomaly_vals[_i];
  if (isnan(val))
    ck_assert_int_eq(isnan(actual(val)), isnan(expected(val)));
  else if (isinf(val))
    ck_assert_int_eq(isinf(actual(val)), isinf(expected(val)));
  else
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_DEFAULT);
}
END_TEST

Suite *suite_s21_sin() {
  Suite *suite = suite_create("suite_s21_sin");

  TCase *normal_case = tcase_create("s21_sin_normal_vals");
  tcase_add_loop_test(normal_case, sin_test_normal, 0,
                      sizeof(normal_vals) / sizeof(normal_vals[0]));
  suite_add_tcase(suite, normal_case);

  TCase *normal_case_loop = tcase_create("s21_sin_normal_vals_loop");
  tcase_add_test(normal_case_loop, sin_test_normal_loop);
  suite_add_tcase(suite, normal_case_loop);

  TCase *normal_case_PI_fract = tcase_create("s21_sin_normal_vals_PI_fract");
  tcase_add_loop_test(normal_case_PI_fract, sin_test_normal_PI_fract, -10, 10);
  suite_add_tcase(suite, normal_case_PI_fract);

  TCase *normal_case_PI_whole = tcase_create("s21_sin_normal_vals_PI_whole");
  tcase_add_loop_test(normal_case_PI_whole, sin_test_normal_PI_whole, -10, 10);
  suite_add_tcase(suite, normal_case_PI_whole);

  TCase *edge_case = tcase_create("s21_sin_edge_vals");
  tcase_add_loop_test(edge_case, sin_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("s21_sin_anomaly_vals");
  tcase_add_loop_test(anomaly_case, sin_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}

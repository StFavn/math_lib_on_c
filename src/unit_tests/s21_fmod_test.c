#include "s21_math_test.h"

#define actual(x, y) s21_fmod(x, y)
#define expected(x, y) fmodl(x, y)

static double normal_vals_x[] = {4,   5,  4.0, 4.5, 5.0,  4,    4.0,
                                 4.0, -4, -5,  -5,  -5.0, -5.0, 12.0};

static double normal_vals_y[] = {2,   2, 2, 2,  2.1, 5,    5,
                                 5.0, 2, 2, -2, 4.0, -4.5, 4};

START_TEST(fmod_test_normal) {
  double val_x = normal_vals_x[_i];
  double val_y = normal_vals_y[_i];

  ck_assert_ldouble_eq_tol(actual(val_x, val_y), expected(val_x, val_y),
                           S21_EPS_HIGH);
}
END_TEST

START_TEST(fmod_test_normal_loop_x) {
  const double delim_y = 0.5;
  const double step = 0.1;
  double start = -100;
  double end = 100;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(actual(start, delim_y), expected(start, delim_y),
                             S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

START_TEST(fmod_test_normal_loop_y) {
  const double delim_x = 0.5;
  const double step = 0.1;
  double start = -100;
  double end = 100;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(actual(delim_x, start), expected(delim_x, start),
                             S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

static double edge_vals_x[] = {0.0,     1.0,     -1,     DBL_MAX,
                               DBL_MIN, DBL_MIN, 5343.6, 467.44432};

static double edge_vals_y[] = {1.0,     -1.0,   0,         DBL_MAX,
                               DBL_MIN, 5343.6, 467.44432, 0.666334343534543};

START_TEST(fmod_test_edge) {
  double val_x = edge_vals_x[_i];
  double val_y = edge_vals_y[_i];

  if (isnan(expected(val_x, val_y))) {
    ck_assert_ldouble_nan(actual(val_x, val_y));
  } else {
    ck_assert_ldouble_eq_tol(actual(val_x, val_y), expected(val_x, val_y),
                             S21_EPS_HIGH);
  }
}
END_TEST

static double anomaly_vals_x[] = {
    -0.0, 0.0 / -0.0, INFINITY - 1, -INFINITY + 1, NAN, 5, 5, 5.0, 2, 2, -2};

static double anomaly_vals_y[] = {0 / -0.0, -0.0,     INFINITY,  -INFINITY,
                                  S21_NAN,  INFINITY, -INFINITY, S21_NAN,
                                  5.0,      2,        0.0 / -0.0};

START_TEST(fmod_test_anomaly) {
  double val_x = anomaly_vals_x[_i];
  double val_y = anomaly_vals_y[_i];

  if (isnan(expected(val_x, val_y))) {
    ck_assert_ldouble_nan(actual(val_x, val_y));
  } else {
    ck_assert_ldouble_eq_tol(actual(val_x, val_y), expected(val_x, val_y),
                             S21_EPS_HIGH);
  }
}
END_TEST

Suite *suite_s21_fmod() {
  Suite *suite = suite_create("suite_s21_fmod");

  TCase *normal_case = tcase_create("s21_fmod_normal_vals");
  tcase_add_loop_test(normal_case, fmod_test_normal, 0,
                      sizeof(normal_vals_x) / sizeof(normal_vals_x[0]));
  suite_add_tcase(suite, normal_case);

  TCase *normal_case_loop_x = tcase_create("s21_fmod_normal_vals_loop_x");
  tcase_add_test(normal_case_loop_x, fmod_test_normal_loop_x);
  suite_add_tcase(suite, normal_case_loop_x);

  TCase *normal_case_loop_y = tcase_create("s21_fmod_normal_vals_loop_y");
  tcase_add_test(normal_case_loop_y, fmod_test_normal_loop_y);
  suite_add_tcase(suite, normal_case_loop_y);

  TCase *edge_case = tcase_create("s21_fmod_edge_vals");
  tcase_add_loop_test(edge_case, fmod_test_edge, 0,
                      sizeof(edge_vals_x) / sizeof(edge_vals_x[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("s21_fmod_anomaly_vals");
  tcase_add_loop_test(anomaly_case, fmod_test_anomaly, 0,
                      sizeof(anomaly_vals_x) / sizeof(anomaly_vals_x[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}
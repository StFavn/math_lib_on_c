#include "s21_math_test.h"

#define actual(x) s21_sqrt(x)
#define expected(x) sqrtl(x)

static long double normal_vals[] = {1,
                                    0.1234567,
                                    S21_PI,
                                    S21_PI / 2,
                                    S21_PI / 3,
                                    S21_PI / 6,
                                    4.0,
                                    4.0,
                                    -4,
                                    -5,
                                    -5,
                                    -5.0,
                                    -5.0,
                                    12.0,
                                    3 * S21_PI / 6,
                                    5 * S21_PI / 6};

START_TEST(sqrt_test_normal) {
  double val = normal_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

START_TEST(sqrt_test_normal_loop) {
  double step = 0.01;
  double start = 0;
  double end = 20;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(actual(start), expected(start), S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

// value 1.E-9 raise the error;
static double edge_vals[] = {1.e-8, 0, 10.e+17, FLT_MAX, FLT_MIN, DBL_MIN};

START_TEST(sqrt_test_edge) {
  double val = edge_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

static long double anomaly_vals[] = {0.0, 0. / 0., INFINITY, -INFINITY, NAN};

START_TEST(sqrt_test_anomaly) {
  double val = anomaly_vals[_i];
  if (isnan(expected(val))) {
    ck_assert_ldouble_nan(actual(val));
  } else if (isinf(val)) {
    if (val > 0) ck_assert_ldouble_infinite(actual(val));
    if (val < 0) ck_assert_ldouble_eq(actual(val), expected(val));
  } else {
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
  }
}
END_TEST

Suite *suite_s21_sqrt() {
  Suite *suite = suite_create("suite_s21_sqrt");

  TCase *normal_case = tcase_create("s21_sqrt_edge_vals");
  tcase_add_loop_test(normal_case, sqrt_test_normal, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, normal_case);

  TCase *normal_case_loop = tcase_create("s21_sqrt_normal_vals_loop");
  tcase_add_test(normal_case_loop, sqrt_test_normal_loop);
  suite_add_tcase(suite, normal_case_loop);

  TCase *edge_case = tcase_create("s21_sqrt_edge_vals");
  tcase_add_loop_test(edge_case, sqrt_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("s21_exp_anomaly_vals");
  tcase_add_loop_test(anomaly_case, sqrt_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}

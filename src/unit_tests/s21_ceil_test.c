#include "s21_math_test.h"

#define actual(x) s21_ceil(x)
#define expected(x) ceill(x)

static double normal_vals[] = {-1.056,       -2e-6,        0, 1.785, 42.21,
                               4.5555555563, -0.4546711111};

START_TEST(ceil_test_normal) {
  double val = normal_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

static double edge_vals[] = {FLT_MAX, FLT_MIN, -0, 0, DBL_MAX, DBL_MIN};

START_TEST(ceil_test_edge) {
  double val = edge_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

static double anomaly_vals[] = {NAN, -0.0, 0 / -0.0, INFINITY};

START_TEST(ceil_test_anomaly) {
  double val = anomaly_vals[_i];
  if (isnan(val))
    ck_assert_int_eq(isnan(actual(val)), isnan(expected(val)));
  else if (isinf(val))
    ck_assert_int_eq(isinf(actual(val)), isinf(expected(val)));
  else
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

Suite *suite_s21_ceil() {
  Suite *suite = suite_create("suite_s21_ceil");

  TCase *normal_case = tcase_create("s21_ceil_normal_vals");
  tcase_add_loop_test(normal_case, ceil_test_normal, 0,
                      sizeof(normal_vals) / sizeof(normal_vals[0]));
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("s21_ceil_edge_vals");
  tcase_add_loop_test(edge_case, ceil_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("s21_ceil_anomaly_vals");
  tcase_add_loop_test(anomaly_case, ceil_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}

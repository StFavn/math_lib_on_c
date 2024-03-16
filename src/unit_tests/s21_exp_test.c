#include "s21_math_test.h"

#define actual(x) s21_exp(x)
#define expected(x) expl(x)

START_TEST(exp_test_normal) {
  const double step = 1.e-3;  // 0.0001 is ok, but too long
  double start = -35.;
  double end = 20.;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(actual(start), expected(start), S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

static double edge_vals[] = {1e-9, -0, 0, DBL_MIN, 7.345e-29, -0.567};

START_TEST(exp_test_edge) {
  double val = edge_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
}
END_TEST

static double anomaly_vals[] = {NAN, -0.0, -1 / 0.0, 0. / 0., INFINITY};

START_TEST(exp_test_anomaly) {
  double val = anomaly_vals[_i];
  if (isnan(val)) {
    ck_assert_int_eq(isnan(actual(val)), isnan(expected(val)));
  } else if (isinf(val)) {
    if (val > 0) ck_assert_ldouble_infinite(actual(val));
    if (val < 0) ck_assert_ldouble_eq(actual(val), expected(val));
  } else {
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_HIGH);
  }
}
END_TEST

Suite *suite_s21_exp() {
  Suite *suite = suite_create("suite_s21_exp");

  TCase *normal_case = tcase_create("s21_exp_normal_vals");
  tcase_add_test(normal_case, exp_test_normal);
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("s21_exp_edge_vals");
  tcase_add_loop_test(edge_case, exp_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("s21_exp_anomaly_vals");
  tcase_add_loop_test(anomaly_case, exp_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}

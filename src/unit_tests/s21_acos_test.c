#include "s21_math_test.h"

#define actual(x) s21_acos(x)
#define expected(x) acosl(x)

static long double normal_vals[] = {
    0,       // 0
    0.0,     // 1
    0.5,     // 2
    -0.5,    // 3
    0.01,    // 4
    -0.01,   // 5
    0.9999,  // 6
    -0.9999  // 7
};

START_TEST(acos_test_normal) {
  double val = normal_vals[_i];
  ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_DEFAULT);
}
END_TEST

static double edge_vals[] = {
    1.0,          // 0
    -1.0,         // 1
    4754754453,   // 2
    -4754754453,  // 3
    DBL_MAX,      // 4
    DBL_MIN,      // 5
    -0            // 6
};

START_TEST(acos_test_edge) {
  double val = edge_vals[_i];
  if (isnan(expected(val)))
    ck_assert_ldouble_nan(actual(val));
  else
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_DEFAULT);
}
END_TEST

static double anomaly_vals[] = {
    NAN,       // 0
    INFINITY,  // 1
    -0.0,      // 2
    0 / -0.0,  // 3
    5.5456,    // 4
    -4.563     // 5
};

START_TEST(acos_test_anomaly) {
  double val = anomaly_vals[_i];
  if (isnan(expected(val)))
    ck_assert_ldouble_nan(actual(val));
  else
    ck_assert_ldouble_eq_tol(actual(val), expected(val), S21_EPS_DEFAULT);
}
END_TEST

Suite *suite_s21_acos() {
  Suite *suite = suite_create("suite_s21_acos");

  TCase *normal_case = tcase_create("s21_acos_normal_vals");
  tcase_add_loop_test(normal_case, acos_test_normal, 0,
                      sizeof(normal_vals) / sizeof(normal_vals[0]));
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("s21_acos_edge_vals");
  tcase_add_loop_test(edge_case, acos_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("s21_acos_anomaly_vals");
  tcase_add_loop_test(anomaly_case, acos_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}

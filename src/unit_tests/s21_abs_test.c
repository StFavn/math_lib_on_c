#include "s21_math_test.h"

#define actual(x) s21_abs(x)
#define expected(x) abs(x)

static int normal_vals[] = {1,           2,    3,      -1,    -2,
                            -3,          -100, -45635, 7654,  -0xAFCD,
                            -0b11101001, 895,  123,    -5775, 8};

START_TEST(abs_test_normal) {
  int val = normal_vals[_i];
  ck_assert_int_eq(actual(val), expected(val));
}
END_TEST

static int edge_vals[] = {INT_MAX, INT_MIN, -0, 0};

START_TEST(abs_test_edge) {
  int val = edge_vals[_i];
  ck_assert_int_eq(actual(val), expected(val));
}
END_TEST

static long anomaly_vals[] = {77777777777, -77777777777, -0050620};

START_TEST(abs_test_anomaly) {
  int val = anomaly_vals[_i];
  ck_assert_int_eq(actual(val), expected(val));
}
END_TEST

Suite *suite_s21_abs() {
  Suite *suite = suite_create("suite_s21_abs");

  TCase *normal_case = tcase_create("s21_abs_normal_vals");
  tcase_add_loop_test(normal_case, abs_test_normal, 0,
                      sizeof(normal_vals) / sizeof(normal_vals[0]));
  suite_add_tcase(suite, normal_case);

  TCase *edge_case = tcase_create("s21_abs_edge_vals");
  tcase_add_loop_test(edge_case, abs_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case = tcase_create("s21_abs_anomaly_vals");
  tcase_add_loop_test(anomaly_case, abs_test_anomaly, 0,
                      sizeof(anomaly_vals) / sizeof(anomaly_vals[0]));
  suite_add_tcase(suite, anomaly_case);

  return suite;
}
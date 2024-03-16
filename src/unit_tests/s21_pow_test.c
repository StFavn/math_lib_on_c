#include "s21_math_test.h"

#define actual(x, y) s21_pow(x, y)
#define expected(x, y) powl(x, y)

START_TEST(pow_test_normal_loop) {
  const double step = 1.;
  double start = -5.L;
  double end = 5.L;  // 40 Ok

  double exp_min = -5;  // -16 Ok
  double exp_max = 5;

  while ((end - start) > S21_EPS_HIGH) {
    for (int k = exp_min; k <= exp_max; ++k) {
      if (start != 0) {
        ck_assert_ldouble_eq_tol(actual(start, k), expected(start, k),
                                 S21_EPS_HIGH);
      }
    }
    start += step;
  }
}
END_TEST

START_TEST(pow_test_sqrt_loop) {
  const double step = 1.e-1;  // 1.e-3 ok, but too long
  double start = 0.L;
  double end = 3.L;

  double exp = 0.5;

  while ((end - start) > S21_EPS_HIGH) {
    ck_assert_ldouble_eq_tol(actual(start, exp), expected(start, exp),
                             S21_EPS_HIGH);
    start += step;
  }
}
END_TEST

START_TEST(pow_test_frac_exp_loop) {
  const double step = 1.e-1;  // 0.001 - ok, но очень долго;
  double start = 0.L;         // Fractinal is ok only for numbers > 0
  double end = 1.L;

  double exp_step = 1.e-2;
  double exp_min = -0.5;
  double exp_max = 0.5;

  while ((end - start) > S21_EPS_DEFAULT) {
    for (double k = exp_min; k <= exp_max; k += exp_step) {
      if (start != 0) {
        ck_assert_ldouble_eq_tol(actual(start, k), expected(start, k), 1.e-7L);
      }
    }
    start += step;
  }
}
END_TEST

static double edge_vals[] = {1.234e-43, 1, 1.e+9};  // value > 1.+10 test fail
static double edge_exp[] = {0.95, 0.95, 0.95};

START_TEST(pow_test_edge) {
  double val = edge_vals[_i];
  double exponent = edge_exp[_i];
  ck_assert_ldouble_eq_tol(actual(val, exponent), expected(val, exponent),
                           S21_EPS_DEFAULT);
}
END_TEST

START_TEST(pow_test_anomaly_01) {
  ck_assert_int_eq(isnan(actual(-3.14, 3.14)), isnan(expected(-3.14, 3.14)));
  ck_assert_int_eq(isnan(actual(NAN, 3.14)), isnan(expected(NAN, 3.14)));
  ck_assert_int_eq(isnan(actual(2.45, NAN)), isnan(expected(2.45, NAN)));
}
END_TEST

START_TEST(pow_test_anomaly_02) {
  ck_assert_ldouble_eq_tol(actual(1., NAN), expected(1., NAN), S21_EPS_HIGH);
  ck_assert_ldouble_eq_tol(actual(1., -2.45), expected(1., -2.45),
                           S21_EPS_HIGH);
}
END_TEST

START_TEST(pow_test_anomaly_03) {
  ck_assert_ldouble_eq_tol(actual(NAN, 0), expected(NAN, 0), S21_EPS_HIGH);
  ck_assert_ldouble_eq_tol(actual(-2.45, 0), expected(-2.45, 0), S21_EPS_HIGH);
}
END_TEST

START_TEST(pow_test_anomaly_04) {
  ck_assert_int_eq(s21_is_negative_zero(actual(-0.0, 3.)),
                   s21_is_negative_zero(expected(-0.0, 3.)));
  ck_assert_int_eq(s21_is_negative_zero(actual(+0.0, 3.)),
                   s21_is_negative_zero(expected(+0.0, 3.)));
}
END_TEST

START_TEST(pow_test_anomaly_05) {
  ck_assert_int_eq(!s21_is_negative_zero(actual(-0.0, 4.)),
                   !s21_is_negative_zero(expected(-0.0, 4.)));
  ck_assert_int_eq(s21_is_negative_zero(actual(+0.0, 4.)),
                   s21_is_negative_zero(expected(+0.0, 4.)));
}
END_TEST

START_TEST(pow_test_anomaly_06) {
  ck_assert_ldouble_eq_tol(actual(-1., S21_INF), expected(-1., S21_INF),
                           S21_EPS_HIGH);
  ck_assert_ldouble_eq_tol(actual(-1., -S21_INF), expected(-1., -S21_INF),
                           S21_EPS_HIGH);
}
END_TEST

START_TEST(pow_test_anomaly_07) {
  int chek_actual_01 =
      (s21_isinf(actual(0.95, -S21_INF))) && (actual(0.95, -S21_INF) > 0);
  int chek_expected_01 =
      (s21_isinf(expected(0.95, -S21_INF))) && (expected(0.95, -S21_INF) > 0);
  int chek_actual_02 =
      (s21_isinf(actual(-0.145, -S21_INF))) && (actual(-0.145, -S21_INF) > 0);
  int chek_expected_02 = (s21_isinf(expected(-0.145, -S21_INF))) &&
                         (expected(-0.145, -S21_INF) > 0);
  ck_assert_int_eq(chek_actual_01, chek_expected_01);
  ck_assert_int_eq(chek_actual_02, chek_expected_02);
}
END_TEST

START_TEST(pow_test_anomaly_08) {
  int chek_actual_01 = ((actual(1.95, -S21_INF) == 0.0) &&
                        !s21_is_negative_zero(actual(1.95, -S21_INF)));
  int chek_expected_01 = ((expected(1.95, -S21_INF) == 0.0) &&
                          !s21_is_negative_zero(expected(1.95, -S21_INF)));
  int chek_actual_02 = ((actual(-1.145, -S21_INF) == 0.0) &&
                        !s21_is_negative_zero(actual(-1.145, -S21_INF)));
  int chek_expected_02 = ((expected(-1.145, -S21_INF) == 0.0) &&
                          !s21_is_negative_zero(expected(-1.145, -S21_INF)));
  ck_assert_int_eq(chek_actual_01, chek_expected_01);
  ck_assert_int_eq(chek_actual_02, chek_expected_02);
}
END_TEST

START_TEST(pow_test_anomaly_09) {
  int chek_actual_01 = ((actual(0.95, S21_INF) == 0.0) &&
                        !s21_is_negative_zero(actual(0.95, S21_INF)));
  int chek_expected_01 = ((expected(0.95, S21_INF) == 0.0) &&
                          !s21_is_negative_zero(expected(0.95, S21_INF)));
  int chek_actual_02 = ((actual(-0.145, S21_INF) == 0.0) &&
                        !s21_is_negative_zero(actual(-0.145, S21_INF)));
  int chek_expected_02 = ((expected(-0.145, S21_INF) == 0.0) &&
                          !s21_is_negative_zero(expected(-0.145, S21_INF)));
  ck_assert_int_eq(chek_actual_01, chek_expected_01);
  ck_assert_int_eq(chek_actual_02, chek_expected_02);
}
END_TEST

START_TEST(pow_test_anomaly_10) {
  int chek_actual_01 =
      (s21_isinf(actual(1.95, S21_INF))) && (actual(1.95, S21_INF) > 0);
  int chek_expected_01 =
      (s21_isinf(expected(1.95, S21_INF))) && (expected(1.95, S21_INF) > 0);
  int chek_actual_02 =
      (s21_isinf(actual(-1.145, S21_INF))) && (actual(-1.145, S21_INF) > 0);
  int chek_expected_02 =
      (s21_isinf(expected(-1.145, S21_INF))) && (expected(-1.145, S21_INF) > 0);
  ck_assert_int_eq(chek_actual_01, chek_expected_01);
  ck_assert_int_eq(chek_actual_02, chek_expected_02);
}
END_TEST

START_TEST(pow_test_anomaly_11) {
  ck_assert_int_eq(s21_is_negative_zero(actual(-S21_INF, -3)),
                   s21_is_negative_zero(expected(-S21_INF, -3)));
  ck_assert_int_eq(!s21_is_negative_zero(actual(-S21_INF, -4)),
                   !s21_is_negative_zero(expected(-S21_INF, -4)));
}
END_TEST

START_TEST(pow_test_anomaly_12) {
  int chek_actual_01 =
      s21_isinf(actual(-S21_INF, 3)) && (actual(-S21_INF, 3) < 0);
  int chek_expected_01 =
      s21_isinf(expected(-S21_INF, 3)) && (expected(-S21_INF, 3) < 0);
  ck_assert_int_eq(chek_actual_01, chek_expected_01);
}
END_TEST

START_TEST(pow_test_anomaly_13) {
  int chek_actual_01 =
      s21_isinf(actual(-S21_INF, 4)) && (actual(-S21_INF, 4) > 0);
  int chek_expected_01 =
      s21_isinf(expected(-S21_INF, 4)) && (expected(-S21_INF, 4) > 0);
  ck_assert_int_eq(chek_actual_01, chek_expected_01);
}
END_TEST

START_TEST(pow_test_anomaly_14) {
  ck_assert_int_eq(!s21_is_negative_zero(actual(S21_INF, -1.425)),
                   !s21_is_negative_zero(expected(S21_INF, -1.425)));
  ck_assert_ldouble_eq(actual(S21_INF, 1.425), expected(S21_INF, 1.425));
}
END_TEST

START_TEST(pow_test_zero_neg) {
  double num = 0;
  double p = -1;
  ck_assert_ldouble_infinite(actual(num, p));
  ck_assert_ldouble_infinite(expected(num, p));
}

START_TEST(pow_test_zero_pos) {
  double num = 0;
  double p = 1;
  ck_assert_ldouble_eq_tol(actual(num, p), expected(num, p), S21_APPRX_DEFAULT);
}

Suite *suite_s21_pow() {
  Suite *suite = suite_create("suite_s21_pow");

  TCase *normal_case_loop = tcase_create("s21_pow_normal_vals");
  tcase_add_test(normal_case_loop, pow_test_normal_loop);
  suite_add_tcase(suite, normal_case_loop);

  TCase *sqrt_exp_case_loop = tcase_create("s21_pow_sqrt_vals");
  tcase_add_test(sqrt_exp_case_loop, pow_test_sqrt_loop);
  suite_add_tcase(suite, sqrt_exp_case_loop);

  TCase *frac_exp_case_loop = tcase_create("s21_pow_frac_exp_vals");
  tcase_add_test(frac_exp_case_loop, pow_test_frac_exp_loop);
  suite_add_tcase(suite, frac_exp_case_loop);

  TCase *edge_case = tcase_create("s21_pow_edge_vals");
  tcase_add_loop_test(edge_case, pow_test_edge, 0,
                      sizeof(edge_vals) / sizeof(edge_vals[0]));
  suite_add_tcase(suite, edge_case);

  TCase *anomaly_case_01 = tcase_create("s21_pow_anomaly_vals_01");
  tcase_add_test(anomaly_case_01, pow_test_anomaly_01);
  suite_add_tcase(suite, anomaly_case_01);

  TCase *anomaly_case_02 = tcase_create("s21_pow_anomaly_vals_02");
  tcase_add_test(anomaly_case_02, pow_test_anomaly_02);
  suite_add_tcase(suite, anomaly_case_02);

  TCase *anomaly_case_03 = tcase_create("s21_pow_anomaly_vals_03");
  tcase_add_test(anomaly_case_03, pow_test_anomaly_03);
  suite_add_tcase(suite, anomaly_case_03);

  TCase *anomaly_case_04 = tcase_create("s21_pow_anomaly_vals_04");
  tcase_add_test(anomaly_case_04, pow_test_anomaly_04);
  suite_add_tcase(suite, anomaly_case_04);

  TCase *anomaly_case_05 = tcase_create("s21_pow_anomaly_vals_05");
  tcase_add_test(anomaly_case_05, pow_test_anomaly_05);
  suite_add_tcase(suite, anomaly_case_05);

  TCase *anomaly_case_06 = tcase_create("s21_pow_anomaly_vals_06");
  tcase_add_test(anomaly_case_06, pow_test_anomaly_06);
  suite_add_tcase(suite, anomaly_case_06);

  TCase *anomaly_case_07 = tcase_create("s21_pow_anomaly_vals_07");
  tcase_add_test(anomaly_case_07, pow_test_anomaly_07);
  suite_add_tcase(suite, anomaly_case_07);

  TCase *anomaly_case_08 = tcase_create("s21_pow_anomaly_vals_08");
  tcase_add_test(anomaly_case_08, pow_test_anomaly_08);
  suite_add_tcase(suite, anomaly_case_08);

  TCase *anomaly_case_09 = tcase_create("s21_pow_anomaly_vals_09");
  tcase_add_test(anomaly_case_09, pow_test_anomaly_09);
  suite_add_tcase(suite, anomaly_case_09);

  TCase *anomaly_case_10 = tcase_create("s21_pow_anomaly_vals_10");
  tcase_add_test(anomaly_case_10, pow_test_anomaly_10);
  suite_add_tcase(suite, anomaly_case_10);

  TCase *anomaly_case_11 = tcase_create("s21_pow_anomaly_vals_11");
  tcase_add_test(anomaly_case_11, pow_test_anomaly_11);
  suite_add_tcase(suite, anomaly_case_11);

  TCase *anomaly_case_12 = tcase_create("s21_pow_anomaly_vals_12");
  tcase_add_test(anomaly_case_12, pow_test_anomaly_12);
  suite_add_tcase(suite, anomaly_case_12);

  TCase *anomaly_case_13 = tcase_create("s21_pow_anomaly_vals_13");
  tcase_add_test(anomaly_case_13, pow_test_anomaly_13);
  suite_add_tcase(suite, anomaly_case_13);

  TCase *anomaly_case_14 = tcase_create("s21_pow_anomaly_vals_14");
  tcase_add_test(anomaly_case_14, pow_test_anomaly_14);
  suite_add_tcase(suite, anomaly_case_14);

  TCase *anomaly_zero_neg = tcase_create("s21_pow_test_zero_neg");
  tcase_add_test(anomaly_zero_neg, pow_test_zero_neg);
  suite_add_tcase(suite, anomaly_zero_neg);

  TCase *anomaly_zero_pos = tcase_create("s21_pow_test_zero_pos");
  tcase_add_test(anomaly_zero_pos, pow_test_zero_pos);
  suite_add_tcase(suite, anomaly_zero_pos);

  return suite;
}
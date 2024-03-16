#include "s21_math_test.h"

#define actual(x, y) s21_pow_int(x, y)
#define expected(x, y) powl(x, y)

START_TEST(pow_int_test_normal) {
  const long double step = 1;
  long double start = -20.L;
  long double end = 40.L;

  int exp_min = -16;
  int exp_max = 12;  // 17 get error at e+21

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

Suite *suite_s21_pow_int() {
  Suite *suite = suite_create("suite_s21_pow_int");

  TCase *normal_case = tcase_create("s21_pow_int_normal_vals");
  tcase_add_test(normal_case, pow_int_test_normal);
  suite_add_tcase(suite, normal_case);

  return suite;
}

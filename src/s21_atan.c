#include "s21_math.h"

long double s21_atan(double x) {
  if (s21_isnan(x) || x == 0) return x;
  if (s21_isinf(x)) {
    if (x < 0) return -S21_PI_DIV_2;
    if (x > 0) return S21_PI_DIV_2;
  }

  if ((s21_fabs(1 - s21_fabs(x)) < S21_EPS_HIGH)) {
    return (x > 0) ? S21_PI_DIV_4 : -S21_PI_DIV_4;
  }

  long double apprx = S21_APPRX_DEFAULT;

  // approximation tuning for e-6 accuracy arg close to 1.
  if (s21_fabs(x) < 0.9999999 && s21_fabs(x) > 0.999) apprx = 1.77e+5;

  long double ld_x = x;
  long double res = 0;

  if (s21_fabs(ld_x) < 1.) {
    for (int i = 0; i < apprx; ++i) {
      long double sign = (s21_isodd(i)) ? -1 : 1;
      long double numerator = sign * s21_pow_int(ld_x, (1 + 2 * i));
      long double denominator = 1 + 2 * i;
      res += numerator / denominator;
    }
  }

  if (s21_fabs(ld_x) > 1.) {
    long double d_numerator = S21_PI * s21_fabs(ld_x);
    long double d_denominator = 2 * ld_x;
    long double d_res = d_numerator / d_denominator;

    for (int i = 0; i < apprx; ++i) {
      long double sign = (s21_isodd(i)) ? -1 : 1;
      long double numerator = sign * s21_pow_int(ld_x, (-1 - 2 * i));
      long double denominator = 1 + 2 * i;
      res += numerator / denominator;
    }
    res = d_res - res;
  }

  return res;
}
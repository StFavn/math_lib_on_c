#include "s21_math.h"

long double s21_sin(double x) {
  if (s21_isnan(x) || s21_isinf(x)) return S21_NAN;

  const long double ld_x = s21_fmod(x, 2.0 * S21_PI);
  const long double x_squared = ld_x * ld_x;

  long double res = ld_x;
  long double stage_val = ld_x;

  for (int k = 1; k <= S21_APPRX_DEFAULT; ++k) {
    stage_val *= -(x_squared / ((2 * k) * (2 * k + 1)));
    res += stage_val;
  }

  return res;
}
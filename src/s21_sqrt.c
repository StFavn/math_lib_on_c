#include "s21_math.h"

#define S21_SQRT_EPS 1e-20L

long double s21_sqrt(double x) {
  if ((x < 0) || s21_isnan(x)) return S21_NAN;

  if ((x <= S21_SQRT_EPS) || s21_isinf(x)) return x;

  const long double ld_x = x;
  const long double denom = 2.L;

  long double res = x / denom;
  long double temp = 0;

  while (s21_fabs(res - temp) > S21_EPS_HIGH) {
    temp = res;
    res = (ld_x / temp + temp) / denom;
  }

  return res;
}

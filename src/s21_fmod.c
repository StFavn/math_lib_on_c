#include "s21_math.h"

long double s21_fmod(double x, double y) {
  if (s21_isnan(x) || s21_isnan(y) || s21_isinf(x) || s21_iszero(y))
    return S21_NAN;

  if (s21_isinf(y)) return x;
  if (s21_iszero(x) && !s21_iszero(y)) return 0.L;

  long double int_div_res = s21_modf(x / y);
  long double res = (x - (int_div_res * y));
  return res;
}

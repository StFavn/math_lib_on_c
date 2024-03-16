#include "s21_math.h"

long double s21_ceil(double x) {
  if (s21_isnan(x) || s21_iszero(x) || s21_isinteger(x) || s21_isinf(x))
    return x;

  long double res = s21_modf(s21_fabs(x));

  int sign = (x < 0) ? -1 : 1;
  if (sign == 1) ++res;

  return (sign * res);
}
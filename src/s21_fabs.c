#include "s21_math.h"

long double s21_fabs(double x) {
  if (s21_isnan(x)) return S21_NAN;
  if (s21_iszero(x)) return 0.0L;
  if (s21_isinf(x)) return S21_INF;

  long double res = x;
  return (res < 0) ? -res : res;
}
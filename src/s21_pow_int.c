#include "s21_math.h"

long double s21_pow_int(long double base, int exp) {
  if (exp == 0) return 1.L;
  if (exp == 1) return base;
  if ((exp < 0) && (base == 0)) return S21_INF;

  long double res = 1.L;
  int m_exp = s21_abs(exp);

  while (m_exp != 0) {
    if (s21_isodd(m_exp)) res *= base;
    base *= base;
    m_exp /= 2;
  }

  return (exp < 0) ? (1 / res) : res;
}
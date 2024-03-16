#include "s21_math.h"

#define S21_EXP_BORDER 19.5

static long double s21_exp_complex(double x);
static long double s21_exp_series(double x);

long double s21_exp(double x) {
  if (s21_isnan(x)) return x;
  if (s21_isinf(x)) {
    if (x < 0) return 0.;
    if (x > 0) return S21_INF;
  }

  return (x <= S21_EXP_BORDER) ? s21_exp_complex(x) : s21_exp_series(x);
}

/// Good for small and meduim numbers,
/// then 'x' below 19.5 (S21_EXP_BORDER)
/// Use formula: e^x * e^y = e^(x + y)
static long double s21_exp_complex(double x) {
  const double integral_part = s21_modf(x);
  const double fractional_part = x - integral_part;

  long double fractional = 1;
  if (fractional_part != 0) {
    fractional = s21_exp_series(fractional_part);
  }

  long double integral = s21_pow_int(S21_E, integral_part);
  return (integral * fractional);
}

/// Good for big numbers, for 'x' more
/// than 19.5 (S21_EXP_BORDER)
static long double s21_exp_series(double x) {
  const long double ld_x = x;
  long double res = 1;
  long double stage_val = 1;

  for (int k = 1; k <= S21_APPRX_DEFAULT; ++k) {
    stage_val *= ld_x / k;
    res += stage_val;
  }

  return res;
}

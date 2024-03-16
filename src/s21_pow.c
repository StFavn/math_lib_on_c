#include "s21_math.h"

typedef struct pow_flags {
  bool base_is_one;
  bool exp_is_close_integer;
  bool exp_is_integer;
} pow_flags;

long double s21_pow_compute(double base, double exp, pow_flags flags);

long double s21_pow(double base, double exp) {
  if (exp == 0) return 1.0L;

  pow_flags flags = {false};

  if (s21_isinteger(exp)) {
    flags.exp_is_integer = true;
  }

  if ((s21_fabs(exp) - s21_fabs(s21_modf(exp))) < S21_EPS_HIGH) {
    flags.exp_is_close_integer = true;
  }

  if (!s21_isnan(base)) {
    flags.base_is_one = (s21_fabs(1 - s21_fabs(base)) < S21_EPS_HIGH);
  }

  // if change on flags.exp_is_close_integer - anomaly test fail
  if (base < 0 && !flags.exp_is_integer) return S21_NAN;
  if (!flags.base_is_one && (s21_isnan(base) || s21_isnan(exp))) return S21_NAN;
  if (flags.base_is_one && (base > 0 && s21_isnan(exp))) return 1.0L;

  if (base == 0) {
    if (exp > 0 && (flags.exp_is_integer && s21_isodd(exp))) {
      if (s21_is_negative_zero(base))
        return -0.0L;
      else
        return 0.0L;
    } else if (exp < 0) {
      return S21_INF;
    } else {
      return 0.0L;
    }
  }

  if ((flags.base_is_one && (base < 0)) && s21_isinf(exp)) return 1.0;
  if ((s21_fabs(base) < 1) && (s21_isinf(exp) && exp < 0)) return S21_INF;
  if ((s21_fabs(base) > 1) && (s21_isinf(exp) && exp < 0)) return +0.0L;
  if ((s21_fabs(base) < 1) && (s21_isinf(exp) && exp > 0)) return +0.0L;
  if ((s21_fabs(base) > 1) && (s21_isinf(exp) && exp > 0)) return S21_INF;

  if (s21_isinf(base)) {
    if (base < 0) {
      if ((exp < 0) && (flags.exp_is_integer && s21_isodd(exp))) return -0.0L;
      if ((exp < 0) && (flags.exp_is_integer && !s21_isodd(exp))) return 0.0L;
      if ((exp > 0) && (flags.exp_is_integer && s21_isodd(exp)))
        return -S21_INF;
      if ((exp > 0) && (flags.exp_is_integer && !s21_isodd(exp)))
        return S21_INF;
    } else if (base > 0) {
      if (exp < 0) return 0.0L;
      if (exp > 0) return S21_INF;
    }
  }
  return s21_pow_compute(base, exp, flags);
}

long double s21_pow_compute(double base, double exp, pow_flags flags) {
  // If `base == 1` in any case -> `return 1`
  // + sign change control if the degree is integer and odd
  if (flags.base_is_one) {
    if (flags.exp_is_integer) {
      return (base < 0 && s21_isodd(exp)) ? -1.L : 1.L;
    } else {
      return base;
    }
  }

  // Degree integer (up to S21_EPS_HIGH) -> use `s21_pow_int()`
  if (flags.exp_is_close_integer)
    return s21_pow_int((long double)base, (int)exp);
  // The degree is +0.5 -> calculate the root of base
  if ((exp > 0) && (s21_fabs(0.5L - exp) < S21_EPS_HIGH)) return s21_sqrt(base);

  // Calculate formula: `a^(x + y) = a^x * a^y`
  double integral_part = s21_modf(exp);
  double fraction_part = exp - integral_part;

  int sign = (base < 0) ? -1 : 1;
  long double integral_res = s21_pow_int(base, integral_part);
  long double fractional_res = s21_exp(fraction_part * s21_log(base * sign));

  return (integral_res * fractional_res);
}
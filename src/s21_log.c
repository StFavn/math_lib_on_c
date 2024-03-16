#include "s21_math.h"

/*
 * The function calculates the natural logarithm using Newton's method.
 * First, the function finds the approximate value of `res` of the logarithm,
 * making `x` less than or equal to the `e` (the base of the natural logarithm),
 * and increasing `res` by one for each division. The function then refines the
 * value of `res` using Newton's method iterations until the value of `res`
 * stabilizes (that is, it stops changing from iteration to iteration) or until
 * the maximum number of iterations is reached (in this case `APPRX_DEFAULT`).
 *
 * Newton's method is used to find the roots of the equation, and in this case
 * it is used to solve the equation `e^N = x` with respect to `N`, which is
 * equivalent to calculating `N = log(x)`.
 */
long double s21_log(double x) {
  if (s21_isnan(x) || (x == -S21_INF) || (x < 0)) return S21_NAN;
  if (x == S21_INF) return S21_INF;
  if (x == 0) return -S21_INF;
  if (x == 1) return 0;

  long double ld_x = x;
  double res = 0.L;

  while (ld_x >= S21_E) {
    ld_x /= S21_E;
    ++res;
  }

  res += (ld_x / S21_E);
  ld_x = x;

  int i = 0;
  double search_apprx = 0.;
  do {
    search_apprx = res;
    double left = (ld_x / (s21_exp(res - 1.0)));
    double right = ((res - 1.0) * S21_E);
    res = ((left + right) / S21_E);
    i++;
  } while ((res != search_apprx) && (i < S21_APPRX_DEFAULT));

  return res;
}
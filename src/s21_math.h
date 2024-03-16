#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdbool.h>

#define S21_EPS_HIGH 1.e-9L
#define S21_EPS_DEFAULT 1.e-6L

#define S21_APPRX_DEFAULT 1200

#define S21_INF (1.0 / 0.0)
#define S21_NAN (0.0 / 0.0)

#define S21_NEGZERO -0.0

#define S21_PI 3.14159265358979323846L
#define S21_PI_DIV_2 1.57079632679489661923L
#define S21_PI_DIV_4 0.78539816339744830961L

#define S21_E 2.71828182845904523536028747L
#define S21_LN2 0.693147180559945309417232L

#define s21_isnan(x) (x != x)
#define s21_isinf(x) ((x == S21_INF) || (x == -S21_INF))
#define s21_isodd(x) (((long long int)x % 2) != 0)
#define s21_iszero(x) ((x == 0.0) || (x == S21_NEGZERO))
#define s21_is_negative_zero(x) ((1 / x) == -1 / 0.0)

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_ceil(double x);
long double s21_exp(double x);
long double s21_fmod(double x, double y);
long double s21_sqrt(double x);
long double s21_log(double x);
long double s21_pow(double base, double exp);

long double s21_cos(double x);
long double s21_sin(double x);
long double s21_tan(double x);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);

bool s21_isinteger(double x);
long double s21_pow_int(long double base, int exp);
/// Get integer part of double(64 bit) number
double s21_modf(double x);

#endif  // SRC_S21_MATH_H_
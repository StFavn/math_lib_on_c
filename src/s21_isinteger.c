#include "s21_binary.h"
#include "s21_math.h"

bool s21_isinteger(double x) {
  if (x == 0) return true;

  union {
    double num;
    unsigned long int data;
  } x_bits = {x};

  int exponent = (int)(x_bits.data >> S21_BIN_DBL_PREC & 0x7ff) - 0x3ff;
  unsigned long int mask =
      -1ULL >> (S21_BIN_DBL_EXP + S21_BIN_DBL_SIGN) >> exponent;

  bool res = false;

  if (exponent < 0)
    res = false;
  else if ((exponent >= S21_BIN_DBL_PREC) || ((x_bits.data & mask) == 0))
    res = true;

  return res;
}
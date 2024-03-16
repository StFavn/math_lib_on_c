#include "s21_binary.h"
#include "s21_math.h"

double s21_modf(double x) {
  if (s21_isnan(x)) return S21_NAN;
  if (s21_isinf(x)) return x;

  union {
    double num;
    unsigned long int data;
  } x_bits = {x};

  // Вычисление размера экспонента в битах, зная параметры хранения double в
  // памяти
  int exponent = (int)(x_bits.data >> S21_BIN_DBL_PREC & 0x7ff) - 0x3ff;

  // По документации - условие для no fractional part
  if (exponent >= S21_BIN_DBL_PREC) return x;

  // По документации - условие для no integral part
  if (exponent < 0) {
    x_bits.data &=
        1ULL << (S21_BIN_DBL_EXP +
                 S21_BIN_DBL_PREC);  // смещение на 63 бита (64 - 1 бит знака)
    return x_bits.num;
  }

  // Вычисление целой части числа, используя мантиссу, экспоненту
  // и формулу из википедии через битовые операции
  unsigned long int mask =
      -1ULL >> (S21_BIN_DBL_EXP + S21_BIN_DBL_SIGN) >> exponent;

  if ((x_bits.data & mask) == 0) return x;  // Число без дробной части;

  x_bits.data &= ~mask;

  return x_bits.num;
}
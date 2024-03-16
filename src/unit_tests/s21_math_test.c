#include "s21_math_test.h"

#include <stdio.h>

void run_suite(Suite *suite) {
  SRunner *sr = srunner_create(suite);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

void run_core_tests() {
  Suite *suites_core[] = {
      suite_s21_abs(),  suite_s21_fabs(), suite_s21_floor(), suite_s21_ceil(),
      suite_s21_exp(),  suite_s21_cos(),  suite_s21_sin(),   suite_s21_fmod(),
      suite_s21_sqrt(), suite_s21_log(),  suite_s21_atan(),  suite_s21_tan(),
      suite_s21_asin(), suite_s21_acos(), suite_s21_pow(),   NULL};

  for (Suite **cur = suites_core; *cur != NULL; cur++) {
    run_suite(*cur);
  }
}

void run_utils_tests() {
  Suite *suites_utils[] = {suite_s21_modf(), suite_s21_pow_int(),
                           suite_s21_isinteger(), NULL};

  for (Suite **cur = suites_utils; *cur != NULL; cur++) {
    run_suite(*cur);
  }
}

void run_tests() {
  printf("\n=========================================\n");
  printf("Core unit-tests:\n\n");
  run_core_tests();

  printf("\n-----------------------------------------\n");
  printf("Utils unit-tests:\n\n");
  run_utils_tests();

  printf("\n=========================================\n");
}

int main() {
  run_tests();
  return 0;
}

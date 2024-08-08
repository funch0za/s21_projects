#include "test_s21_matrix.h"

unsigned int run_suite(Suite *suite, char *file_logs) {
  // создаем раней
  SRunner *srunner = srunner_create(suite);

  // результаты записываем в файл
  srunner_set_log(srunner, file_logs);
  srunner_run_all(srunner, CK_ENV);
  // кол-во зафейленых тестов
  int count_failed_tests = srunner_ntests_failed(srunner);

  // освобождаем память которая была определена для ранера
  srunner_free(srunner);

  return count_failed_tests;
}

int main() {
  int count_failed_tests = 0;

#if TEST_CREATE
  count_failed_tests +=
      run_suite(test_s21_create_remove_matrix_suite(),
                "test/logs/test_s21_create_remove_matrix.log");
#endif

#if TEST_EQ
  count_failed_tests +=
      run_suite(test_s21_eq_matrix_suite(), "test/logs/test_s21_eq_matrix.log");
#endif

#if TEST_SUM
  count_failed_tests += run_suite(test_s21_sum_matrix_suite(),
                                  "test/logs/test_s21_sum_matrix.log");
#endif

#if TEST_SUB
  count_failed_tests += run_suite(test_s21_sub_matrix_suite(),
                                  "test/logs/test_s21_sub_matrix.log");
#endif

#if TEST_MULT_NUMBER
  count_failed_tests += run_suite(test_s21_mult_number_suite(),
                                  "test/logs/test_s21_mult_number.log");
#endif

#if TEST_MULT_MATRIX
  count_failed_tests += run_suite(test_s21_mult_matrix_suite(),
                                  "test/logs/test_s21_mult_matrix.log");
#endif

#if TEST_DETERMINANT
  count_failed_tests += run_suite(test_s21_determinant_suite(),
                                  "test/logs/test_s21_determinant.log");
#endif

#if TEST_TRANSPOSE
  count_failed_tests +=
      run_suite(test_s21_transpose_suite(), "test/logs/test_s21_transpose.log");
#endif

#if TEST_CALC_COMPLEMENTS
  count_failed_tests += run_suite(test_s21_calc_complements_suite(),
                                  "test/logs/test_s21_calc_complements.log");
#endif

#if TEST_INVERSE
  count_failed_tests += run_suite(test_s21_inverse_matrix_suite(),
                                  "test/logs/test_s21_inverse_matrix.log");
#endif

  return count_failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
#include "test_s21_matrix.h"

START_TEST(s21_create_remove_matrix) {
  int rows = 10, columns = 20;

  matrix_t a;

  s21_init_ok_matrix(&a, rows, columns);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(s21_create_matrix_failed) {
  int rows = -1, columns = 0;

  matrix_t a;

  ck_assert_int_eq(INCORRECT_MATRIX, s21_create_matrix(rows, columns, &a));
}
END_TEST

Suite *test_s21_create_remove_matrix_suite() {
  Suite *suite = suite_create("s21_create_remove_matrix");

  TCase *tc = tcase_create("s21_create_matrix_tc");
  tcase_add_test(tc, s21_create_remove_matrix);
  tcase_add_test(tc, s21_create_matrix_failed);

  suite_add_tcase(suite, tc);

  return suite;
}

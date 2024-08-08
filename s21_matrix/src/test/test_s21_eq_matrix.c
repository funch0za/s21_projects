#include <check.h>

#include "test_s21_matrix.h"

START_TEST(two_eq_matrix) {
  matrix_t a, b;
  int rows = 5, columns = 3;

  s21_init_ok_matrix(&a, rows, columns);
  s21_init_ok_matrix(&b, rows, columns);

  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = ((double)(i - j) * 2) / 7;
      b.matrix[i][j] = a.matrix[i][j];
    }
  }

  ck_assert_int_eq(SUCCESS, s21_eq_matrix(&a, &b));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(two_diff_matrix) {
  matrix_t a, b;
  int rows = 5, columns = 3;

  s21_init_ok_matrix(&a, rows, columns);
  s21_init_ok_matrix(&b, rows, columns);

  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = ((double)(i - j) * 2) / 7;
      b.matrix[i][j] = a.matrix[i][j];
    }
  }
  b.matrix[0][0] = -345;

  ck_assert_int_eq(FAILURE, s21_eq_matrix(&a, &b));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(diff_size) {
  matrix_t a, b;

  s21_init_ok_matrix(&a, 102, 108);
  s21_init_ok_matrix(&b, 107, 12);

  ck_assert_int_eq(FAILURE, s21_eq_matrix(&a, &b));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

START_TEST(null) {
  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);
  ck_assert_int_eq(FAILURE, s21_eq_matrix(&a, NULL));
  ck_assert_int_eq(FAILURE, s21_eq_matrix(NULL, &a));
  ck_assert_int_eq(FAILURE, s21_eq_matrix(NULL, NULL));

  s21_remove_matrix(&a);
}
END_TEST

Suite *test_s21_eq_matrix_suite() {
  Suite *suite = suite_create("s21_eq_matrix_suite");

  TCase *tc = tcase_create("s21_eq_matrix_tc");
  tcase_add_test(tc, two_eq_matrix);
  tcase_add_test(tc, two_diff_matrix);
  tcase_add_test(tc, diff_size);
  tcase_add_test(tc, null);

  suite_add_tcase(suite, tc);

  return suite;
}

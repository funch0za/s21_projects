#include "test_s21_matrix.h"

START_TEST(ok_matrix_1_1) {
  int n = 1;
  matrix_t a;
  s21_init_ok_matrix(&a, n, n);
  a.matrix[0][0] = 4.002;

  matrix_t result;
  ck_assert_int_eq(OK, s21_transpose(&a, &result));

  s21_ok_sizes(&result, a.rows, a.columns);
  ck_assert_int_eq(result.matrix[0][0], a.matrix[0][0]);

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(null) {
  matrix_t result;
  ck_assert_int_eq(INCORRECT_MATRIX, s21_transpose(NULL, &result));

  matrix_t a;
  s21_init_ok_matrix(&a, 1, 1);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_transpose(&a, NULL));

  ck_assert_int_eq(INCORRECT_MATRIX, s21_transpose(NULL, NULL));

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(ok_square) {
  int n = 3;
  const double matrix_a[3][3] = {{0.04, 3, 2}, {-4, 108, 105}, {0.3, 9, 9}};

  matrix_t a;
  s21_init_ok_matrix(&a, n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a.matrix[i][j] = matrix_a[i][j];
    }
  }

  matrix_t result;
  ck_assert_int_eq(OK, s21_transpose(&a, &result));
  s21_ok_sizes(&result, n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ck_assert_double_eq(a.matrix[j][i], result.matrix[i][j]);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(ok_vector) {
  int rows = 1, columns = 6;

  matrix_t a;
  s21_init_ok_matrix(&a, rows, columns);
  for (int i = 0; i < columns; ++i) {
    a.matrix[0][i] = i;
  }

  matrix_t result;
  ck_assert_int_eq(OK, s21_transpose(&a, &result));

  s21_ok_sizes(&result, columns, rows);
  for (int i = 0; i < columns; ++i) {
    ck_assert_double_eq(result.matrix[i][0], a.matrix[0][i]);
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

Suite *test_s21_transpose_suite() {
  Suite *suite = suite_create("s21_transpose_suite");

  TCase *tc = tcase_create("s21_transpose_tc");
  tcase_add_test(tc, ok_matrix_1_1);
  tcase_add_test(tc, null);
  tcase_add_test(tc, ok_square);
  tcase_add_test(tc, ok_vector);

  suite_add_tcase(suite, tc);

  return suite;
}

#include "test_s21_matrix.h"

void s21_ok_sizes(matrix_t *a, int rows, int columns) {
  ck_assert_int_eq(a->rows, rows);
  ck_assert_int_eq(a->columns, columns);
}

void s21_init_ok_matrix(matrix_t *a, int rows, int columns) {
  ck_assert_int_gt(rows, 0);
  ck_assert_int_gt(columns, 0);

  ck_assert_int_eq(OK, s21_create_matrix(rows, columns, a));

  s21_ok_sizes(a, rows, columns);
}
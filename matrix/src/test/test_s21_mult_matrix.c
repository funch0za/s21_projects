#include "test_s21_matrix.h"

START_TEST(ok_matrix_1_1) {
  int n = 1;
  matrix_t a, b;

  s21_init_ok_matrix(&a, n, n);
  s21_init_ok_matrix(&b, n, n);
  a.matrix[0][0] = 0.04;
  b.matrix[0][0] = 12;

  matrix_t result;
  ck_assert_int_eq(OK, s21_mult_matrix(&a, &b, &result));
  ck_assert_double_eq(result.matrix[0][0], 0.48);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(incorrect_size_1) {
  matrix_t a, b;

  s21_init_ok_matrix(&a, 102, 108);
  s21_init_ok_matrix(&b, 107, 12);

  matrix_t result;
  ck_assert_int_eq(CALC_ERROR, s21_mult_matrix(&a, &b, &result));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

START_TEST(incorrect_size_2) {
  matrix_t a, b;

  s21_init_ok_matrix(&a, 100, 108);
  s21_init_ok_matrix(&b, 100, 12);

  matrix_t result;
  ck_assert_int_eq(CALC_ERROR, s21_mult_matrix(&a, &b, &result));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

START_TEST(null) {
  matrix_t result;

  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_matrix(NULL, NULL, &result));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_matrix(&a, NULL, &result));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_matrix(NULL, &a, &result));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_matrix(NULL, &a, NULL));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_matrix(&a, NULL, NULL));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_matrix(NULL, NULL, NULL));

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(overflow_1) {
  int n = 1;
  matrix_t a, b;

  s21_init_ok_matrix(&a, n, n);
  s21_init_ok_matrix(&b, n, n);
  a.matrix[0][0] = DBL_MAX;
  b.matrix[0][0] = 222;

  matrix_t result;
  ck_assert_int_eq(CALC_ERROR, s21_mult_matrix(&a, &b, &result));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(ok) {
  const int rows_a = 3, columns_a = 5, rows_b = columns_a, columns_b = 2;

  const double matrix_a[3][5] = {
      {0.04, 3, 2, 33, 0}, {-4, 108, 105, 19, 34}, {0.3, 9, 9, 0, 3}};

  const double matrix_b[5][2] = {
      {12, 0.4}, {34.3, 0.001}, {4, 4}, {4, 1}, {0, 1}};

  const double matrix_result[3][2] = {
      {243.38, 41.019}, {4152.4, 471.508}, {348.3, 39.129}};

  matrix_t a, b;
  s21_init_ok_matrix(&a, rows_a, columns_a);
  s21_init_ok_matrix(&b, rows_b, columns_b);

  for (int i = 0; i < rows_a; ++i) {
    for (int j = 0; j < columns_a; ++j) {
      a.matrix[i][j] = matrix_a[i][j];
    }
  }
  for (int i = 0; i < rows_b; ++i) {
    for (int j = 0; j < columns_b; ++j) {
      b.matrix[i][j] = matrix_b[i][j];
    }
  }

  matrix_t result;
  ck_assert_int_eq(OK, s21_mult_matrix(&a, &b, &result));

  for (int i = 0; i < result.rows; ++i) {
    for (int j = 0; j < result.columns; ++j) {
      ck_assert_double_eq(matrix_result[i][j], result.matrix[i][j]);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

Suite *test_s21_mult_matrix_suite() {
  Suite *suite = suite_create("s21_mult_matrix_suite");

  TCase *tc = tcase_create("s21_mult_matrix_tc");
  tcase_add_test(tc, ok_matrix_1_1);
  tcase_add_test(tc, incorrect_size_1);
  tcase_add_test(tc, incorrect_size_2);
  tcase_add_test(tc, null);
  tcase_add_test(tc, overflow_1);
  tcase_add_test(tc, ok);

  suite_add_tcase(suite, tc);

  return suite;
}
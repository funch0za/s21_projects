#include "test_s21_matrix.h"

START_TEST(overflow_matrix_1_1) {
  matrix_t a, b;
  int rows = 1, columns = 1;

  s21_init_ok_matrix(&a, rows, columns);
  s21_init_ok_matrix(&b, rows, columns);

  a.matrix[0][0] = DBL_MIN;
  b.matrix[0][0] = nextafter(DBL_MIN, 0.0);

  matrix_t res;

  ck_assert_int_eq(CALC_ERROR, s21_sub_matrix(&a, &b, &res));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(ok_matrix_1_1) {
  matrix_t a, b;
  int rows = 1, columns = 1;

  s21_init_ok_matrix(&a, rows, columns);
  s21_init_ok_matrix(&b, rows, columns);

  a.matrix[0][0] = 3;
  b.matrix[0][0] = 2;

  matrix_t res;
  ck_assert_int_eq(OK, s21_sub_matrix(&a, &b, &res));

  s21_ok_sizes(&res, rows, columns);

  ck_assert_int_eq(1, res.matrix[0][0]);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(diff_size) {
  matrix_t a, b;

  s21_init_ok_matrix(&a, 102, 108);
  s21_init_ok_matrix(&b, 107, 12);

  matrix_t res;
  ck_assert_int_eq(CALC_ERROR, s21_sub_matrix(&a, &b, &res));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

START_TEST(incorrect_matrix) {
  matrix_t a, b;
  s21_init_ok_matrix(&a, 3, 3);
  s21_init_ok_matrix(&b, 3, 3);
  matrix_t res;

  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(NULL, NULL, NULL));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(NULL, NULL, &res));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(&a, NULL, &res));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(NULL, &a, &res));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(&a, NULL, NULL));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(&a, &b, NULL));
  ck_assert_int_eq(INCORRECT_MATRIX, s21_sub_matrix(NULL, &b, NULL));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(super_test) {
  int rows = 3, columns = 5;
  matrix_t a, b, ok_res;

  s21_init_ok_matrix(&a, rows, columns);
  s21_init_ok_matrix(&b, rows, columns);
  s21_init_ok_matrix(&ok_res, rows, columns);

  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = ((double)i + 100 - (double)j * 89.01) / 102;
      b.matrix[i][j] = i - j + 808;
      ok_res.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
    }
  }

  matrix_t res;
  ck_assert_int_eq(OK, s21_sub_matrix(&a, &b, &res));
  ck_assert_int_eq(SUCCESS, s21_eq_matrix(&ok_res, &res));

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&ok_res);
  s21_remove_matrix(&res);
}

Suite *test_s21_sub_matrix_suite() {
  Suite *suite = suite_create("s21_sub_matrix_suite");

  TCase *tc = tcase_create("s21_sub_matrix_tc");
  tcase_add_test(tc, overflow_matrix_1_1);
  tcase_add_test(tc, ok_matrix_1_1);
  tcase_add_test(tc, diff_size);
  tcase_add_test(tc, incorrect_matrix);
  tcase_add_test(tc, super_test);

  suite_add_tcase(suite, tc);

  return suite;
}

#include <check.h>
#include <stdio.h>

#include "test_s21_matrix.h"

START_TEST(zero_determinant) {
  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a.matrix[i][j] = i * 3 + j + 1;
    }
  }

  matrix_t result;
  ck_assert_int_eq(CALC_ERROR, s21_inverse_matrix(&a, &result));

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(null) {
  ck_assert_int_eq(INCORRECT_MATRIX, s21_inverse_matrix(NULL, NULL));

  matrix_t res;
  ck_assert_int_eq(INCORRECT_MATRIX, s21_inverse_matrix(NULL, &res));

  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_inverse_matrix(&a, NULL));

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(ok_1) {
  const int a_copy[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);
  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = a_copy[i][j];
    }
  }

  const int ok_result[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t result;
  ck_assert_int_eq(OK, s21_inverse_matrix(&a, &result));
  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      ck_assert_double_eq(result.matrix[i][j], ok_result[i][j]);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(overflow) {
  const double a_copy[3][3] = {{2, DBL_MAX, 7}, {6, 3, 4}, {5, -2, -3}};
  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);
  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = a_copy[i][j];
    }
  }
  matrix_t result;
  ck_assert_int_eq(CALC_ERROR, s21_inverse_matrix(&a, &result));
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(ok_2) {
  const double a_copy[2][2] = {{3, 4}, {1, 2}};
  matrix_t a;
  s21_init_ok_matrix(&a, 2, 2);
  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = a_copy[i][j];
    }
  }

  matrix_t E;
  s21_init_ok_matrix(&E, 2, 2);
  E.matrix[0][0] = 1;
  E.matrix[1][1] = 1;

  matrix_t result;
  ck_assert_int_eq(OK, s21_inverse_matrix(&a, &result));

  matrix_t mult;
  ck_assert_int_eq(OK, s21_mult_matrix(&a, &result, &mult));

  ck_assert_int_eq(SUCCESS, s21_eq_matrix(&E, &mult));

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&E);
  s21_remove_matrix(&mult);
}
END_TEST

START_TEST(ok_3) {
  const double a_copy[3][3] = {{1, -2, 3}, {0, 4, -1}, {5, 0, 1}};
  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);
  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = a_copy[i][j];
    }
  }

  matrix_t E;
  s21_init_ok_matrix(&E, 3, 3);
  E.matrix[0][0] = 1;
  E.matrix[1][1] = 1;
  E.matrix[2][2] = 1;

  matrix_t result;
  ck_assert_int_eq(OK, s21_inverse_matrix(&a, &result));

  matrix_t mult;
  ck_assert_int_eq(OK, s21_mult_matrix(&a, &result, &mult));

  ck_assert_int_eq(SUCCESS, s21_eq_matrix(&E, &mult));

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&E);
  s21_remove_matrix(&mult);
}
END_TEST

Suite *test_s21_inverse_matrix_suite() {
  Suite *suite = suite_create("s21_inverse_matrix_suite");

  TCase *tc = tcase_create("s21_inverse_matrix_tc");
  tcase_add_test(tc, zero_determinant);
  tcase_add_test(tc, null);
  tcase_add_test(tc, ok_1);
  tcase_add_test(tc, overflow);
  tcase_add_test(tc, ok_2);
  tcase_add_test(tc, ok_3);

  suite_add_tcase(suite, tc);

  return suite;
}

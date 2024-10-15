#include <check.h>
#include <math.h>

#include "test_s21_matrix.h"

START_TEST(ok_matrix_1_1) {
  int n = 1;
  matrix_t a;
  s21_init_ok_matrix(&a, n, n);
  a.matrix[0][0] = 4.002;

  double result;
  ck_assert_int_eq(OK, s21_determinant(&a, &result));

  ck_assert_double_eq(result, a.matrix[0][0]);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(incorrect_size_1) {
  matrix_t a;
  s21_init_ok_matrix(&a, 102, 108);

  double result;
  ck_assert_int_eq(CALC_ERROR, s21_determinant(&a, &result));

  s21_remove_matrix(&a);
}

START_TEST(null) {
  double result;
  ck_assert_int_eq(INCORRECT_MATRIX, s21_determinant(NULL, &result));

  matrix_t a;
  s21_init_ok_matrix(&a, 1, 1);
  a.matrix[0][0] = 1;

  ck_assert_int_eq(CALC_ERROR, s21_determinant(&a, NULL));

  ck_assert_int_eq(INCORRECT_MATRIX, s21_determinant(NULL, NULL));

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(overflow) {
  int n = 2;
  matrix_t a;

  s21_init_ok_matrix(&a, n, n);
  a.matrix[0][0] = DBL_MAX;
  a.matrix[0][1] = 20;
  a.matrix[1][0] = -20;
  a.matrix[1][1] = 1000;

  double result;

  ck_assert_int_eq(CALC_ERROR, s21_determinant(&a, &result));
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(ok_1) {
  int n = 3;
  const double matrix_a[3][3] = {{0.04, 3, 2}, {-4, 108, 105}, {0.3, 9, 9}};

  matrix_t a;
  s21_init_ok_matrix(&a, n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a.matrix[i][j] = matrix_a[i][j];
    }
  }

  double result;

  ck_assert_int_eq(OK, s21_determinant(&a, &result));
  ck_assert_double_eq(66.78, result);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(ok_2) {
  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a.matrix[i][j] = i * 3 + j + 1;
    }
  }

  double result;

  ck_assert_int_eq(OK, s21_determinant(&a, &result));
  ck_assert_double_eq(0.0, result);

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(nan_test) {
  matrix_t a;
  s21_init_ok_matrix(&a, 1, 1);
  a.matrix[0][0] = NAN;

  double result;

  ck_assert_int_eq(CALC_ERROR, s21_determinant(&a, &result));

  s21_remove_matrix(&a);
}
END_TEST

Suite *test_s21_determinant_suite() {
  Suite *suite = suite_create("s21_determinant_suite");

  TCase *tc = tcase_create("s21_determinant_tc");
  tcase_add_test(tc, ok_matrix_1_1);
  tcase_add_test(tc, incorrect_size_1);
  tcase_add_test(tc, null);
  tcase_add_test(tc, overflow);
  tcase_add_test(tc, ok_1);
  tcase_add_test(tc, ok_2);
  tcase_add_test(tc, nan_test);

  suite_add_tcase(suite, tc);

  return suite;
}
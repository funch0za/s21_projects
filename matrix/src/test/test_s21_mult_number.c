#include "check.h"
#include "test_s21_matrix.h"

START_TEST(ok_1) {
  int rows = 3, columns = 4;
  matrix_t a;

  s21_init_ok_matrix(&a, rows, columns);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      a.matrix[i][j] = i + j;
    }
  }

  double number = 34.2;
  matrix_t res;
  ck_assert_int_eq(OK, s21_mult_number(&a, number, &res));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      ck_assert_double_eq(res.matrix[i][j], (i + j) * number);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inf_dbl) {
  int rows = 3, columns = 4;
  matrix_t a;

  s21_init_ok_matrix(&a, rows, columns);

  matrix_t res;
  ck_assert_int_eq(CALC_ERROR, s21_mult_number(&a, INFINITY, &res));

  s21_remove_matrix(&a);
}
END_TEST;

START_TEST(overflow) {
  int rows = 3, columns = 4;
  matrix_t a;

  s21_init_ok_matrix(&a, rows, columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      a.matrix[i][j] = DBL_MAX;
    }
  }

  matrix_t res;
  ck_assert_int_eq(CALC_ERROR, s21_mult_number(&a, 1000, &res));

  s21_remove_matrix(&res);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(incorrect_matrix) {
  matrix_t res;

  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_number(NULL, 100, &res));

  matrix_t a;
  s21_init_ok_matrix(&a, 1, 3);
  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_number(&a, 100, NULL));

  ck_assert_int_eq(INCORRECT_MATRIX, s21_mult_number(NULL, 0, NULL));

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(underflow) {
  int rows = 3, columns = 4;
  matrix_t a;

  s21_init_ok_matrix(&a, rows, columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      a.matrix[i][j] = DBL_MIN;
    }
  }

  matrix_t res;
  ck_assert_int_eq(CALC_ERROR, s21_mult_number(&a, DBL_MIN, &res));

  s21_remove_matrix(&res);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(super_test) {
  int rows = 3, columns = 5;
  matrix_t a, ok_res;
  double number = 0.83;

  s21_init_ok_matrix(&a, rows, columns);
  s21_init_ok_matrix(&ok_res, rows, columns);

  for (int i = 0; i < a.rows; ++i) {
    for (int j = 0; j < a.columns; ++j) {
      a.matrix[i][j] = ((double)i + 100 - (double)j * 89.01) / 102;
      ok_res.matrix[i][j] = a.matrix[i][j] * number;
    }
  }

  matrix_t res;
  ck_assert_int_eq(OK, s21_mult_number(&a, number, &res));
  ck_assert_int_eq(SUCCESS, s21_eq_matrix(&ok_res, &res));

  s21_remove_matrix(&a);
  s21_remove_matrix(&ok_res);
  s21_remove_matrix(&res);
}

Suite *test_s21_mult_number_suite() {
  Suite *suite = suite_create("s21_mult_number_suite");

  TCase *tc = tcase_create("s21_mult_number_tc");
  tcase_add_test(tc, ok_1);
  tcase_add_test(tc, inf_dbl);
  tcase_add_test(tc, incorrect_matrix);
  tcase_add_test(tc, overflow);
  tcase_add_test(tc, underflow);
  tcase_add_test(tc, super_test);

  suite_add_tcase(suite, tc);

  return suite;
}

#include "test_s21_matrix.h"

START_TEST(ok_1) {
  matrix_t ok_result, m, result;
  s21_init_ok_matrix(&ok_result, 3, 3);
  s21_init_ok_matrix(&m, 3, 3);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;

  m.matrix[1][0] = 0;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;

  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  ok_result.matrix[0][0] = 0;
  ok_result.matrix[0][1] = 10;
  ok_result.matrix[0][2] = -20;

  ok_result.matrix[1][0] = 4;
  ok_result.matrix[1][1] = -14;
  ok_result.matrix[1][2] = 8;

  ok_result.matrix[2][0] = -8;
  ok_result.matrix[2][1] = -2;
  ok_result.matrix[2][2] = 4;

  int error_code = s21_calc_complements(&m, &result);

  ck_assert_int_eq(error_code, OK);
  for (int i = 0; i < result.rows; ++i) {
    for (int j = 0; j < result.columns; ++j) {
      ck_assert_double_eq(ok_result.matrix[i][j], result.matrix[i][j]);
    }
  }

  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  s21_remove_matrix(&ok_result);
}
END_TEST

START_TEST(ok_2) {
  const int a_copy[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};

  matrix_t a;
  s21_init_ok_matrix(&a, 3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a.matrix[i][j] = a_copy[i][j];
    }
  }

  const int ok_result[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t result;
  int error_code = s21_calc_complements(&a, &result);

  ck_assert_int_eq(error_code, OK);
  for (int i = 0; i < result.rows; ++i) {
    for (int j = 0; j < result.columns; ++j) {
      ck_assert_double_eq(result.matrix[i][j], ok_result[i][j]);
    }
  }

  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(null) {
  matrix_t result;
  ck_assert_int_eq(INCORRECT_MATRIX, s21_calc_complements(NULL, &result));

  matrix_t a;
  s21_init_ok_matrix(&a, 1, 1);
  ck_assert_int_eq(CALC_ERROR, s21_calc_complements(&a, NULL));

  ck_assert_int_eq(INCORRECT_MATRIX, s21_calc_complements(NULL, NULL));

  s21_remove_matrix(&a);
}
END_TEST

START_TEST(matrix_1_1) {
  matrix_t a, result;
  s21_init_ok_matrix(&a, 1, 1);
  ck_assert_int_eq(CALC_ERROR, s21_calc_complements(&a, &result));
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(incorrect_size) {
  matrix_t a, result;
  s21_init_ok_matrix(&a, 20, 21);
  ck_assert_int_eq(CALC_ERROR, s21_calc_complements(&a, &result));
  s21_remove_matrix(&a);
}
END_TEST

Suite *test_s21_calc_complements_suite() {
  Suite *suite = suite_create("s21_calc_complements_suite");

  TCase *tc = tcase_create("s21_calc_complements_tc");
  tcase_add_test(tc, ok_1);
  tcase_add_test(tc, ok_2);
  tcase_add_test(tc, null);
  tcase_add_test(tc, matrix_1_1);
  tcase_add_test(tc, incorrect_size);

  suite_add_tcase(suite, tc);

  return suite;
}

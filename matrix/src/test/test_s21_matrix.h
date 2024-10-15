#ifndef TEST_S21_MATRIX
#define TEST_S21_MATRIX

#include <check.h>
#include <float.h>

#include "../s21_matrix.h"

// Helpers
void s21_init_ok_matrix(matrix_t *a, int rows, int columns);
void s21_ok_sizes(matrix_t *a, int rows, int columns);
unsigned int run_suite(Suite *suite, char *file_logs);

// Suites
Suite *test_s21_create_remove_matrix_suite();
Suite *test_s21_eq_matrix_suite();
Suite *test_s21_sum_matrix_suite();
Suite *test_s21_sub_matrix_suite();
Suite *test_s21_mult_number_suite();
Suite *test_s21_mult_matrix_suite();
Suite *test_s21_determinant_suite();
Suite *test_s21_transpose_suite();
Suite *test_s21_calc_complements_suite();
Suite *test_s21_inverse_matrix_suite();

// Flags
#define TEST_CREATE 1
#define TEST_EQ 1
#define TEST_SUM 1
#define TEST_SUB 1
#define TEST_MULT_NUMBER 1
#define TEST_MULT_MATRIX 1
#define TEST_DETERMINANT 1
#define TEST_TRANSPOSE 1
#define TEST_CALC_COMPLEMENTS 1
#define TEST_INVERSE 1

#endif
#include "s21_matrix.h"

int s21_check_matrix(matrix_t *A) {
  int error_code = OK;

  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    error_code = INCORRECT_MATRIX;
  }

  return error_code;
}

void s21_double_overflow(int *error_code) {
  if (fetestexcept(FE_OVERFLOW) || fetestexcept(FE_UNDERFLOW)) {
    *error_code = CALC_ERROR;
  }
}

void s21_number_is_ok(int *error_code, double x) {
  if (isinf(x) || isnan(x)) {
    *error_code = CALC_ERROR;
  }
}

// function delete row number x and colum number y in matrix A
int s21_del_row_colum(matrix_t *A, int x, int y, matrix_t *result) {
  int error_code = s21_create_matrix(A->rows - 1, A->rows - 1, result);

  if (error_code == OK) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->rows; ++j) {
        if (i != x && j != y) {
          if (i < x && j < y) {
            result->matrix[i][j] = A->matrix[i][j];
          } else if (i > x && j > y) {
            result->matrix[i - 1][j - 1] = A->matrix[i][j];
          } else if (i > x) {
            result->matrix[i - 1][j] = A->matrix[i][j];
          } else {
            result->matrix[i][j - 1] = A->matrix[i][j];
          }
        }
      }
    }
  }

  return error_code;
}

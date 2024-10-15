#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error_code = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    error_code = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;

    result->matrix = malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
      error_code = CALC_ERROR;
    }
    for (int i = 0; error_code == OK && i < rows; ++i) {
      result->matrix[i] = malloc(columns * sizeof(double));

      if (result->matrix[i] == NULL) {
        error_code = CALC_ERROR;
      }
    }

    for (int i = 0; i < result->rows; ++i) {
      for (int j = 0; j < result->columns; ++j) {
        result->matrix[i][j] = (double)0;
      }
    }
  }

  return error_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; A->matrix != NULL && i < A->rows; ++i) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;

  if (s21_check_matrix(A) == INCORRECT_MATRIX ||
      s21_check_matrix(B) == INCORRECT_MATRIX) {
    result = FAILURE;
  }
  if (result == SUCCESS && (A->rows != B->rows || A->columns != B->columns)) {
    result = FAILURE;
  }

  for (int i = 0; result == SUCCESS && i < A->rows; ++i) {
    for (int j = 0; result == SUCCESS && j < A->columns; ++j) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
        result = FAILURE;
      }
    }
  }

  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = s21_check_matrix(A);
  if (error_code == OK) {
    error_code = s21_check_matrix(B);
  }

  if (error_code == OK) {
    if (A->rows != B->rows || A->columns != B->columns) {
      error_code = CALC_ERROR;
    } else {
      error_code = s21_create_matrix(A->rows, A->columns, result);

      for (int i = 0; error_code == OK && i < result->rows; ++i) {
        for (int j = 0; error_code == OK && j < result->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];

          s21_double_overflow(&error_code);
          s21_number_is_ok(&error_code, result->matrix[i][j]);
        }
      }
    }
  }

  return error_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = s21_check_matrix(A);

  if (error_code == OK) {
    error_code = s21_check_matrix(B);
  }

  if (error_code == OK) {
    if (A->rows != B->rows || A->columns != B->columns) {
      error_code = CALC_ERROR;
    } else {
      error_code = s21_create_matrix(A->rows, A->columns, result);

      for (int i = 0; error_code == OK && i < result->rows; ++i) {
        for (int j = 0; error_code == OK && j < result->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          s21_double_overflow(&error_code);
          s21_number_is_ok(&error_code, result->matrix[i][j]);
        }
      }
    }
  }

  return error_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error_code = s21_check_matrix(A);

  if (isnan(number) || isinf(number)) {
    error_code = CALC_ERROR;
  }

  if (error_code == OK) {
    error_code = s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; error_code == OK && i < result->rows; ++i) {
      for (int j = 0; error_code == OK && j < result->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        s21_double_overflow(&error_code);
        s21_number_is_ok(&error_code, result->matrix[i][j]);
      }
    }
  }

  return error_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = s21_check_matrix(A);
  if (error_code == OK) {
    error_code = s21_check_matrix(B);
  }

  if (error_code == OK && A->columns != B->rows) {
    error_code = CALC_ERROR;
  }

  if (error_code == OK) {
    error_code = s21_create_matrix(A->rows, B->columns, result);

    for (int i = 0; error_code == OK && i < result->rows; ++i) {
      for (int j = 0; error_code == OK && j < result->columns; ++j) {
        for (int k = 0; error_code == OK && k < A->columns; ++k) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];

          s21_double_overflow(&error_code);
          s21_number_is_ok(&error_code, result->matrix[i][j]);
        }
      }
    }
  }

  return error_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error_code = s21_check_matrix(A);

  if (error_code == OK) {
    error_code = s21_create_matrix(A->columns, A->rows, result);

    for (int i = 0; error_code == OK && i < result->rows; ++i) {
      for (int j = 0; error_code == OK && j < result->columns; ++j) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }

  return error_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int error_code = s21_check_matrix(A);

  if (error_code == OK && result == NULL) {
    error_code = CALC_ERROR;
  }

  if (error_code == OK && A->rows != A->columns) {
    error_code = CALC_ERROR;
  }

  if (error_code == OK) {
    *result = 0;

    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
      s21_double_overflow(&error_code);
    } else {
      for (int i = 0; error_code == OK && i < A->rows; ++i) {
        matrix_t copy;
        if (s21_del_row_colum(A, i, 0, &copy) == OK) {
          double plus;
          // get minor
          error_code = s21_determinant(&copy, &plus);
          // + (minor * matrix[i][0] * (-1) ^ (i + 0))
          if (i % 2 == 1) {
            plus *= -1;
          }
          plus *= A->matrix[i][0];
          *result += plus;

          s21_double_overflow(&error_code);

          s21_remove_matrix(&copy);
        } else {
          error_code = CALC_ERROR;
        }
      }
    }
  }

  if (error_code == OK) {
    s21_number_is_ok(&error_code, *result);
  }
  return error_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error_code = s21_check_matrix(A);

  if (error_code == OK && (A->rows != A->columns || A->rows < 2)) {
    error_code = CALC_ERROR;
  } else if (error_code == OK) {
    error_code = s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; error_code == OK && i < A->rows; ++i) {
      for (int j = 0; error_code == OK && j < A->columns; ++j) {
        matrix_t copy;

        if (s21_del_row_colum(A, i, j, &copy) == OK) {
          double minor;
          error_code = s21_determinant(&copy, &minor);
          result->matrix[i][j] = minor;

          if ((i + j) % 2 == 1) {
            result->matrix[i][j] *= -1;
          }

          s21_double_overflow(&error_code);
          s21_remove_matrix(&copy);
        } else {
          error_code = CALC_ERROR;
          s21_remove_matrix(result);
        }
      }
    }
  }

  return error_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error_code = s21_check_matrix(A);
  if (error_code == OK && result == NULL) {
    error_code = INCORRECT_MATRIX;
  }

  double determinant;
  if (error_code == OK) {
    error_code = s21_determinant(A, &determinant);
    if (determinant == 0) {
      error_code = CALC_ERROR;
    }
  }

  if (error_code == OK) {
    matrix_t A_complements;
    error_code = s21_calc_complements(A, &A_complements);

    if (error_code == OK) {
      matrix_t A_complements_trans;
      error_code = s21_transpose(&A_complements, &A_complements_trans);
      s21_remove_matrix(&A_complements);

      if (error_code == OK) {
        error_code =
            s21_mult_number(&A_complements_trans, 1 / determinant, result);
        s21_remove_matrix(&A_complements_trans);
      }
    }
  }

  return error_code;
}

#ifndef S21_MATRIX
#define S21_MATRIX

#include <fenv.h>
#include <math.h>
#include <stdlib.h>

// Structure of matrix
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Helpers
int s21_check_matrix(matrix_t *A);
int s21_del_row_colum(matrix_t *A, int x, int y, matrix_t *result);
void s21_double_overflow(int *error_code);
void s21_number_is_ok(int *error_code, double x);

// Error codes for operations
#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2

// Operations
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7
int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#include <stdio.h>

void print_matrix(matrix_t *A);

#endif
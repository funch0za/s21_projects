#include "test_s21_matrix_plus.h"

/*
 * TEST MULT NUMBER
 */

TEST(TestMultNum, TestMultNum1) {
  S21Matrix a(23, 33), b(a.GetRows(), a.GetCols());

  a.MulNumber(100);
  EXPECT_TRUE(a == b);
}

TEST(TestMultNum, TestMultNum2) {
  S21Matrix a(23, 33), b(a.GetRows(), a.GetCols());
  const double num = 1.2005;
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      a.SetElement(i, j, i * j * 0.8 - i * 0.001 + j * 0.5 + (i + j) * 1.2452);
      b.SetElement(i, j, a(i, j) * num);
    }
  }

  a.MulNumber(num);

  EXPECT_TRUE(a == b);
}

/*
 * TEST OPERATOR
 */

TEST(TestMultNum, TestOperator1) {
  S21Matrix a(23, 33), b(a.GetRows(), a.GetCols());

  S21Matrix result = a * 100;
  a *= 100;

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(a == result);
}

TEST(TestMultNum, TestOperator2) {
  S21Matrix a(23, 33), b(a.GetRows(), a.GetCols());
  const double num = 1.2005;
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      a.SetElement(i, j, i * j * 0.8 - i * 0.001 + j * 0.5 + (i + j) * 1.2452);
      b.SetElement(i, j, a(i, j) * num);
    }
  }

  S21Matrix result = a * num;
  a *= num;

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(result == a);
}

/*
 * MULT MATRIX
 */

TEST(TestMulMatrix, TestMulMatrix1) {
  const size_t rows_a = 3, columns_a = 5, rows_b = columns_a, columns_b = 2;
  const double matrix_a[rows_a][columns_a] = {
      {0.04, 3, 2, 33, 0}, {-4, 108, 105, 19, 34}, {0.3, 9, 9, 0, 3}};
  const double matrix_b[rows_b][columns_b] = {
      {12, 0.4}, {34.3, 0.001}, {4, 4}, {4, 1}, {0, 1}};
  const size_t rows_result = 3, columns_result = 2;
  const double matrix_result[3][2] = {
      {243.38, 41.019}, {4152.4, 471.508}, {348.3, 39.129}};
  
  S21Matrix a(rows_a, columns_a);
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      a.SetElement(i, j, matrix_a[i][j]);
    }
  }

  S21Matrix b(rows_b, columns_b);
  for (size_t i = 0; i < b.GetRows(); ++i) {
    for (size_t j = 0; j < b.GetCols(); ++j) {
      b.SetElement(i, j, matrix_b[i][j]);
    }
  }
  
  S21Matrix result(rows_result, columns_result);
  for (size_t i = 0; i < result.GetRows(); ++i) {
    for (size_t j = 0; j < result.GetCols(); ++j) {
      result.SetElement(i, j, matrix_result[i][j]);
    }
  }
  
  S21Matrix a_copy(a);
  S21Matrix buffer = a * b;
  a.MulMatrix(b);
  a_copy *= b;

  EXPECT_TRUE(a == result);
  EXPECT_TRUE(a == buffer);
  EXPECT_TRUE(a_copy == result);
}

TEST(TestMultMatrix, TestMulMatrix2) {
  S21Matrix a(2, 3), b(100, 23);

  EXPECT_ANY_THROW(a *= b);
}

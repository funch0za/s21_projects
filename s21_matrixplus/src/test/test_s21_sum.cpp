#include "test_s21_matrix_plus.h"

/*
 * TEST SUM
 */

TEST(TestSum, TestSum1) {
  S21Matrix a(1, 1), b(1, 1);
  a.SetElement(0, 0, 23);
  b.SetElement(0, 0, 45);

  S21Matrix sum(1, 1);
  sum.SetElement(0, 0, a(0, 0) + b(0, 0));
  a.SumMatrix(b);

  EXPECT_TRUE(a == sum);
}

#define FORMULA_A_TEST2 (i * j - 121 + i - j)
#define FORMULA_B_TEST2 ((double)i / j - 23.34 - 0.0001)

TEST(TestSum, TestSum2) {
  size_t rows = 10, cols = 20;
  S21Matrix a(rows, cols), b(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      a.SetElement(i, j, FORMULA_A_TEST2);
      b.SetElement(i, j, FORMULA_B_TEST2);
    }
  }
  a.SumMatrix(b);

  S21Matrix sum(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      sum.SetElement(i, j, FORMULA_A_TEST2 + FORMULA_B_TEST2);
    }
  }

  EXPECT_TRUE(a == sum);
}

/*
 * TEST OPERATOR *=
 */

TEST(TestSum, TestOperator1) {
  S21Matrix a(1, 1), b(1, 1);
  a.SetElement(0, 0, 23);
  b.SetElement(0, 0, 45);

  S21Matrix sum(1, 1);
  sum.SetElement(0, 0, a(0, 0) + b(0, 0));

  a += b;

  EXPECT_TRUE(a == sum);
}

TEST(TestSum, TestOperator2) {
  size_t rows = 10, cols = 20;
  S21Matrix a(rows, cols), b(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      a.SetElement(i, j, FORMULA_A_TEST2);
      b.SetElement(i, j, FORMULA_B_TEST2);
    }
  }

  S21Matrix sum(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      sum.SetElement(i, j, FORMULA_A_TEST2 + FORMULA_B_TEST2);
    }
  }

  a += b;

  EXPECT_TRUE(a == sum);
}

TEST(TestSum, TestOperator3) {
  size_t rows = 4, cols = 3;

  S21Matrix a(rows, cols), b(rows, cols), sum(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      a.SetElement(i, j, i + j);
      b.SetElement(i, j, 1);
      sum.SetElement(i, j, i + j + 1);
    }
  }

  a += b;

  EXPECT_TRUE(a == sum);
}

TEST(TestSum, TestThrow) {
  S21Matrix a(10, 100), b(34, 45);

  EXPECT_ANY_THROW(a += b);
  EXPECT_ANY_THROW(a.SumMatrix(b));
  S21Matrix c;
  EXPECT_ANY_THROW(c = a + b);
}

/*
 * TEST OPERATOR *
 */

TEST(TestSum, TestOperatorBuf1) {
  size_t rows = 10, cols = 20;
  S21Matrix a(rows, cols), b(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      a.SetElement(i, j, FORMULA_A_TEST2);
      b.SetElement(i, j, FORMULA_B_TEST2);
    }
  }

  S21Matrix result = a + b;

  S21Matrix sum(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      sum.SetElement(i, j, FORMULA_A_TEST2 + FORMULA_B_TEST2);
    }
  }

  EXPECT_TRUE(result == sum);
}

TEST(TestSum, TestOperatorBuf2) {
  S21Matrix a(1, 1), b(1, 1);
  a.SetElement(0, 0, 23);
  b.SetElement(0, 0, 45);

  S21Matrix sum(1, 1);
  sum.SetElement(0, 0, a(0, 0) + b(0, 0));

  S21Matrix result = a + b;

  EXPECT_TRUE(result == sum);
}

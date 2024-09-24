#include "test_s21_matrix_plus.h"

/*
 * TEST SUB
 */

TEST(TestSub, TestSub1) {
  S21Matrix a(1, 1), b(1, 1);
  a.SetElement(0, 0, 23);
  b.SetElement(0, 0, 45);

  S21Matrix sub(1, 1);
  sub.SetElement(0, 0, a(0, 0) - b(0, 0));
  a.SubMatrix(b);

  EXPECT_TRUE(a == sub);
}

#define FORMULA_A_TEST2 (i * j - 121 + i - j)
#define FORMULA_B_TEST2 ((double)i / j - 23.34 - 0.0001)

TEST(TestSub, TestSub2) {
  size_t rows = 10, cols = 20;
  S21Matrix a(rows, cols), b(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      a.SetElement(i, j, FORMULA_A_TEST2);
      b.SetElement(i, j, FORMULA_B_TEST2);
    }
  }
  a.SubMatrix(b);

  S21Matrix sub(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      sub.SetElement(i, j, FORMULA_A_TEST2 - FORMULA_B_TEST2);
    }
  }

  EXPECT_TRUE(a == sub);
}

/*
 * TEST OPERATOR
 */

TEST(TestSub, TestOperator1) {
  S21Matrix a(1, 1), b(1, 1);
  a.SetElement(0, 0, 23);
  b.SetElement(0, 0, 45);

  S21Matrix sub(1, 1);
  sub.SetElement(0, 0, a(0, 0) - b(0, 0));

  S21Matrix result;
  result = a - b;
  a -= b;

  EXPECT_TRUE(a == sub);
  EXPECT_TRUE(a == result);
}

TEST(TestSub, TestOperator2) {
  size_t rows = 10, cols = 20;
  S21Matrix a(rows, cols), b(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      a.SetElement(i, j, FORMULA_A_TEST2);
      b.SetElement(i, j, FORMULA_B_TEST2);
    }
  }

  S21Matrix sub(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      sub.SetElement(i, j, FORMULA_A_TEST2 - FORMULA_B_TEST2);
    }
  }

  S21Matrix result;
  result = a - b;
  a -= b;

  EXPECT_TRUE(a == sub);
  EXPECT_TRUE(a == result);
}

TEST(TestSub, TestIncorrectSize) {
  S21Matrix a(100, 100), b(1, 1);
  EXPECT_ANY_THROW(a - b);
  EXPECT_ANY_THROW(a -= b);
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

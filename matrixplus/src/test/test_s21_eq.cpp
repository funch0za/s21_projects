#include "test_s21_matrix_plus.h"

TEST(TestEq, TestEqOperation1) {
  size_t rows = 1, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);

  a.SetElement(0, 0, 13);
  b.SetElement(0, 0, 13);

  EXPECT_TRUE(a.EqMatrix(b) && b.EqMatrix(a));
}

TEST(TestEq, TestEqOperation2) {
  size_t rows = 1, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);

  a.SetElement(0, 0, -12);
  b.SetElement(0, 0, 13);

  EXPECT_FALSE(a.EqMatrix(b) && b.EqMatrix(a));
}

TEST(TestEq, TestEqOperation3) {
  S21Matrix a(102, 100);
  S21Matrix b(5, 3);

  EXPECT_FALSE(a.EqMatrix(b) && b.EqMatrix(a));
}

TEST(TestEq, TestEqOperation4) {
  S21Matrix a;
  S21Matrix b;

  EXPECT_TRUE(a.EqMatrix(b) && b.EqMatrix(a));
}

TEST(TestEq, TestEqOperation5) {
  S21Matrix a(3, 4);

  a.SetElement(0, 0, 4);
  a.SetElement(0, 3, 124);
  a.SetElement(2, 1, 33);
  a.SetElement(1, 1, 422);

  S21Matrix b(a);
  EXPECT_TRUE(a.EqMatrix(b) && b.EqMatrix(a));
}

TEST(TestEq, TestEqOperator1) {
  size_t rows = 1, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);

  a.SetElement(0, 0, 13);
  b.SetElement(0, 0, 13);

  EXPECT_TRUE(a == b && b == a);
}

TEST(TestEq, TestEqOperator2) {
  size_t rows = 1, cols = 1;
  S21Matrix a(rows, cols);
  S21Matrix b(rows, cols);

  a.SetElement(0, 0, -12);
  b.SetElement(0, 0, 13);

  EXPECT_FALSE(a == b && b == a);
}

TEST(TestEq, TestEqOperator3) {
  S21Matrix a(102, 100);
  S21Matrix b(5, 3);

  EXPECT_FALSE(a == b && b == a);
}

TEST(TestEq, TestEqOperator4) {
  S21Matrix a;
  S21Matrix b;

  EXPECT_TRUE(a == b && b == a);
}

TEST(TestEq, TestEqOperator5) {
  S21Matrix a(3, 4);

  a.SetElement(0, 0, 4);
  a.SetElement(0, 3, 124);
  a.SetElement(2, 1, 33);
  a.SetElement(1, 1, 422);

  S21Matrix b(a);
  EXPECT_TRUE(a == b && b == a);
}

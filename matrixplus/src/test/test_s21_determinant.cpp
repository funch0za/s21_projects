#include "test_s21_matrix_plus.h"

TEST(TestDeterminant, Test1) {
  S21Matrix a(1, 1);
  a.SetElement(0, 0, 2.334);
  EXPECT_TRUE(a.Determinant() == a(0, 0));
}

TEST(TestDeterminant, Test2) {
  S21Matrix a(100, 3);
  EXPECT_ANY_THROW(a.Determinant());
}

TEST(TestDeterminant, Test3) {
  const size_t n = 3;
  const double matrix_a[n][n] = {{0.04, 3, 2}, {-4, 108, 105}, {0.3, 9, 9}};
  S21Matrix a(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      a.SetElement(i, j, matrix_a[i][j]);
    }
  }

  EXPECT_TRUE(a.Determinant() == 66.78);
}

TEST(TestDeterminant, Test4) {
  const size_t n = 3;
  S21Matrix a(n, n);
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      a.SetElement(i, j, i * 3 + j + 1);
    }
  }
  EXPECT_TRUE(a.Determinant() == 0.0);
}

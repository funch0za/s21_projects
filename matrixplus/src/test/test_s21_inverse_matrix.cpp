#include "test_s21_matrix_plus.h"
#include <gtest/gtest.h>

TEST(TestInverseMatrix, Test1) {
  const size_t n = 3;
  S21Matrix a(n, n);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      a.SetElement(i, j, i * 3 + j + 1);
    }
  }

  EXPECT_ANY_THROW(a.InverseMatrix());
}

TEST(TestInverseMatrix, Test2) {
  const size_t n = 3;
  const int a_copy[n][n] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  S21Matrix a(n, n);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      a.SetElement(i, j, a_copy[i][j]);
    }
  }

  // A * A ^ (-1) = E
  S21Matrix inverse = a.InverseMatrix();
  S21Matrix mult = a * inverse;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      EXPECT_TRUE((i == j && mult(i, j) == 1) || (i != j && mult(i, j) == 0));
    }
  }
}

TEST(TestInverseMatrix, Test3) {
  S21Matrix a(3, 4);
  EXPECT_ANY_THROW(a.InverseMatrix());
}

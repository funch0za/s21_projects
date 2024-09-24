#include "test_s21_matrix_plus.h"

void test_s21_matrix::constructors::param(size_t rows, size_t cols) {
  S21Matrix m(rows, cols);
  EXPECT_EQ(m.GetRows(), rows);
  EXPECT_EQ(m.GetCols(), cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      EXPECT_EQ(m(i, j), 0);
    }
  }
}

void test_s21_matrix::constructors::copy(int rows, int cols) {
  S21Matrix a(rows, cols);
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      a.SetElement(i, j, i * j);
    }
  }
  S21Matrix b(a);
  EXPECT_TRUE(a == b);
}

void test_s21_matrix::constructors::move(size_t rows, size_t cols) {
  S21Matrix a(rows, cols);
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      a.SetElement(i, j, 21 - i + j);
    }
  }
  S21Matrix b(std::move(a));
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(b.GetCols(), cols);
  EXPECT_EQ(b.GetRows(), rows);

  for (size_t i = 0; i < b.GetRows(); ++i) {
    for (size_t j = 0; j < b.GetCols(); ++j) {
      EXPECT_EQ(b(i, j), 21 - i + j);
    }
  }
}

void test_s21_matrix::constructors::operator_copy(int rows, int cols) {
  S21Matrix a(rows, cols);
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      a.SetElement(i, j, i - double(j) / 2 + 10);
    }
  }

  S21Matrix b;
  b = a;
  EXPECT_TRUE(a == b);
}

void test_s21_matrix::print_matrix(S21Matrix &m) {
  for (size_t i = 0; i < m.GetRows(); ++i) {
    for (size_t j = 0; j < m.GetCols(); ++j) {
      std::cout << m(i, j) << ' ';
    }
    std::cout << '\n';
  }
}

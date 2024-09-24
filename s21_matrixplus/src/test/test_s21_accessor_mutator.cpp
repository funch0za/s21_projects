#include <gtest/gtest.h>

#include <cstddef>

#include "test_s21_matrix_plus.h"

TEST(TestAccessorMutator, TestAccessor) {
  size_t rows = 100, cols = 23;
  S21Matrix a(rows, cols);
  EXPECT_TRUE(a.GetRows() == rows);
  EXPECT_TRUE(a.GetCols() == cols);
}

TEST(TestAccessorMutator, TestMutator1) {
  S21Matrix a(55, 88);
  EXPECT_ANY_THROW(a.SetCols(-1));
  EXPECT_ANY_THROW(a.SetRows(-7));
}

TEST(TestAccessorMutator, TestMutator2) {
  size_t rows = 5, cols = 10;
  S21Matrix a(rows, cols);
  size_t new_rows = 3;
  a.SetRows(new_rows);
  EXPECT_TRUE(a.GetRows() == new_rows);
  size_t new_cols = 12;
  a.SetCols(new_cols);
  EXPECT_TRUE(a.GetCols() == new_cols);
}

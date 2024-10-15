#include "test_s21_matrix_plus.h"

TEST(TestTranspose, Test1) {
  S21Matrix a(5, 5);

  S21Matrix t = a.Transpose();
  EXPECT_TRUE(a == t);
}

TEST(TestTranspose, Test2) {
  S21Matrix a(1, 5);
  for (size_t i = 0; i < a.GetCols(); ++i) {
    a.SetElement(0, i, i);
  }
  
  S21Matrix t = a.Transpose();
  for (size_t i = 0; i < a.GetCols(); ++i) {
    EXPECT_TRUE(a(0, i) == t(i, 0));
  }
}

TEST(TestTranspose, Test3) {
  S21Matrix a(5, 10);
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      a.SetElement(i, j, i * a.GetCols() + j);
    }
  }

  S21Matrix t = a.Transpose();
  for (size_t i = 0; i < a.GetRows(); ++i) {
    for (size_t j = 0; j < a.GetCols(); ++j) {
      EXPECT_TRUE(a(i, j) == t(j, i));
    } 
  }

  t = t.Transpose();
  EXPECT_TRUE(a == t);
}

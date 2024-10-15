#include "test_s21_matrix_plus.h"

TEST(TestGetElementOperator, Test1) {
  S21Matrix a(100, 100);
  EXPECT_TRUE(a(0, 0) == 0 && a(3, 56) == 0);

  size_t i = 34, j = 23;
  double num = 3.41;
  a.SetElement(i, j, num);
  EXPECT_TRUE(a(i, j) == num);

  EXPECT_ANY_THROW(a(-23, 0));
  EXPECT_ANY_THROW(a(4, -8));
}

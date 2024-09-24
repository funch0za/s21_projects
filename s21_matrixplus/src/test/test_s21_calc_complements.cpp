#include "test_s21_matrix_plus.h"

TEST(TestCalcComplements, Test1) {
  const size_t n = 3;
  S21Matrix m(n, n), ok_result(n, n);

  m.SetElement(0, 0, 1);
  m.SetElement(0, 1, 2);
  m.SetElement(0, 2, 3);

  m.SetElement(1, 0, 0);
  m.SetElement(1, 1, 4);
  m.SetElement(1, 2, 2);

  m.SetElement(2, 0, 5);
  m.SetElement(2, 1, 2);
  m.SetElement(2, 2, 1);
  
  ok_result.SetElement(0, 0, 0);
  ok_result.SetElement(0, 1, 10);
  ok_result.SetElement(0, 2, -20);
  
  ok_result.SetElement(1, 0, 4);
  ok_result.SetElement(1, 1, -14);
  ok_result.SetElement(1, 2, 8);

  ok_result.SetElement(2, 0, -8);
  ok_result.SetElement(2, 1, -2);
  ok_result.SetElement(2, 2, 4);

  S21Matrix result = m.CalcComplements();
  EXPECT_TRUE(result == ok_result);
}


#ifndef TEST_S21_MATRIX_PLUS_H
#define TEST_S21_MATRIX_PLUS_H

#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

namespace test_s21_matrix {
  namespace constructors {
    void param(size_t rows, size_t cols);
    void copy(int rows, int cols);
    void move(size_t rows, size_t cols);
    void operator_copy(int rows, int cols);
  }

  void print_matrix(S21Matrix &m);
}



#endif

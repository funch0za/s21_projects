#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (size_t i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
    matrix_[i] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
  matrix_ = 0;
  cols_ = 0;
}

S21Matrix::S21Matrix(const int rows, const int cols) : S21Matrix() {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("incorrect matrix size");
  }
  rows_ = rows;
  cols_ = cols;

  matrix_ = new double* [rows_] { nullptr };
  for (size_t i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0};
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (size_t i = 0; i < other.rows_; ++i) {
    std::copy(other.matrix_[i], other.matrix_[i] + other.cols_,
              matrix_[i]);
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

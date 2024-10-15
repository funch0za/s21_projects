#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (size_t i = 0; i < this->rows_; ++i) {
    delete[] this->matrix_[i];
    this->matrix_[i] = nullptr;
  }
  delete[] this->matrix_;
  this->matrix_ = nullptr;
  this->matrix_ = 0;
  this->cols_ = 0;
}

S21Matrix::S21Matrix(const int rows, const int cols) : S21Matrix() {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("incorrect matrix size");
  }
  this->rows_ = rows;
  this->cols_ = cols;

  this->matrix_ = new double* [this->rows_] { nullptr };
  for (size_t i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_]{0};
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (size_t i = 0; i < other.rows_; ++i) {
    std::copy(other.matrix_[i], other.matrix_[i] + other.cols_,
              this->matrix_[i]);
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

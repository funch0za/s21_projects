#include "s21_matrix_oop.h"

size_t S21Matrix::GetCols() const { return this->cols_; }

size_t S21Matrix::GetRows() const { return this->rows_; }

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument("incorrect matrix size");
  }
  if (size_t(cols) == this->cols_) {
    return;
  }

  S21Matrix buf(*this);
  for (size_t i = 0; i < this->rows_; ++i) {
    delete[] this->matrix_[i];
    matrix_[i] = new double[cols];
    std::copy(buf.matrix_[i],
              buf.matrix_[i] + std::min(size_t(cols), buf.cols_),
              matrix_[i]);
  }
  cols_ = cols;
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("incorrect matrix size");
  }
  if (size_t(rows) == rows_) {
    return;
  }

  S21Matrix buf(*this);
  for (size_t i = 0; i < rows_; ++i) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;

  rows_ = rows;
  matrix_ = new double* [rows_] { nullptr };
  for (size_t i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0};
    std::copy(buf.matrix_[i], buf.matrix_[i] + buf.cols_, matrix_[i]);
  }
}

void S21Matrix::SetElement(int i, int j, double num) {
  CheckIndex(i, j);
  matrix_[i][j] = num;
}

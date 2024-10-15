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
    this->matrix_[i] = new double[cols];
    std::copy(buf.matrix_[i],
              buf.matrix_[i] + std::min(size_t(cols), buf.cols_),
              this->matrix_[i]);
  }
  this->cols_ = cols;
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::invalid_argument("incorrect matrix size");
  }
  if (size_t(rows) == this->rows_) {
    return;
  }

  S21Matrix buf(*this);
  for (size_t i = 0; i < this->rows_; ++i) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;

  this->rows_ = rows;
  this->matrix_ = new double* [this->rows_] { nullptr };
  for (size_t i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_]{0};
    std::copy(buf.matrix_[i], buf.matrix_[i] + buf.cols_, this->matrix_[i]);
  }
}

void S21Matrix::SetElement(int i, int j, double num) {
  this->CheckIndex(i, j);
  this->matrix_[i][j] = num;
}

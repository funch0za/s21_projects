#include <cstddef>

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix buffer(*this);
  buffer.MulMatrix(other);
  return buffer;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix buffer(*this);
  buffer.SumMatrix(other);
  return buffer;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix buffer(*this);
  buffer.SubMatrix(other);
  return buffer;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix buffer(*this);
  buffer.MulNumber(num);
  return buffer;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->rows_ = other.GetRows();
  this->cols_ = other.GetCols();

  this->matrix_ = new double *[this->rows_] { nullptr };
  for (size_t i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_]{0};
    for (size_t j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = other(i, j);
    }
  }

  return *this;
}


S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

const double &S21Matrix::operator()(const int i, const int j) const {
  this->CheckIndex(i, j);
  return this->matrix_[i][j];
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

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
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  rows_ = other.GetRows();
  cols_ = other.GetCols();

  matrix_ = new double *[rows_] { nullptr };
  for (size_t i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{0};
    for (size_t j = 0; j < cols_; ++j) {
      matrix_[i][j] = other(i, j);
    }
  }

  return *this;
}


S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

const double &S21Matrix::operator()(const int i, const int j) const {
  CheckIndex(i, j);
  return matrix_[i][j];
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

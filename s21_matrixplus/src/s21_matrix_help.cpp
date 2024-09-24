#include "s21_matrix_oop.h"

void S21Matrix::CheckIndex(long long i, long long j) const {
  if (0 > i || i >= (long long)this->GetRows()) {
    throw std::range_error("incorrect row index");
  }
  if (0 > j || j >= (long long)this->GetCols()) {
    throw std::range_error("incorrect col index");
  }
}

S21Matrix S21Matrix::DelRow(size_t x, size_t y) const {
  S21Matrix result(this->GetRows() - 1, this->GetCols() - 1);

  for (size_t i = 0; i < this->GetRows(); ++i) {
    for (size_t j = 0; j < this->GetCols(); ++j) {
      if (i != x && j != y) {
        if (i != x && j != y) {
          if (i < x && j < y) {
            result.matrix_[i][j] = this->matrix_[i][j];
          } else if (i > x && j > y) {
            result.matrix_[i - 1][j - 1] = this->matrix_[i][j];
          } else if (i > x) {
            result.matrix_[i - 1][j] = this->matrix_[i][j];
          } else {
            result.matrix_[i][j - 1] = this->matrix_[i][j];
          }
        }
      }
    }
  }

  return result;
}

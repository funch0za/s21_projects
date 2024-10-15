#include "s21_matrix_oop.h"
#include <stdexcept>

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (other.GetRows() != this->GetRows() ||
      other.GetCols() != this->GetCols()) {
    return false;
  }

  for (size_t i = 0; i < this->GetRows(); ++i) {
    for (size_t j = 0; j < this->GetCols(); ++j) {
      if (std::abs(other(i, j) - (*this)(i, j)) >
          std::numeric_limits<double>::epsilon()) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->GetRows() != other.GetRows() ||
      this->GetCols() != other.GetCols()) {
    throw std::logic_error("incorrect matrix size");
  }

  for (size_t i = 0; i < this->GetRows(); ++i) {
    for (size_t j = 0; j < this->GetCols(); ++j) {
      this->matrix_[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->GetRows() != other.GetRows() ||
      this->GetCols() != other.GetCols()) {
    throw std::logic_error("incorrect matrix size");
  }

  for (size_t i = 0; i < this->GetRows(); ++i) {
    for (size_t j = 0; j < this->GetCols(); ++j) {
      this->matrix_[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (size_t i = 0; i < this->GetRows(); ++i) {
    for (size_t j = 0; j < this->GetCols(); ++j) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->GetCols() != other.GetRows()) {
    throw std::logic_error("incorrect matrix size");
  }

  S21Matrix buf(this->GetRows(), other.GetCols());
  for (size_t i = 0; i < buf.GetRows(); ++i) {
    for (size_t j = 0; j < buf.GetCols(); ++j) {
      for (size_t k = 0; k < this->GetCols(); ++k) {
        buf.SetElement(i, j, buf(i, j) + (*this)(i, k) * other(k, j));
      }
    }
  }
    
  *this = buf;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(this->GetCols(), this->GetRows());
  for (size_t i = 0; i < result.rows_; ++i) {
    for (size_t j = 0; j < result.cols_; ++j) {
      result.SetElement(i, j, (*this)(j, i));
    }
  }

  return result;
}

double S21Matrix::Determinant() const {
  if (this->GetCols() != this->GetRows()) {
    throw std::logic_error("incorrect matrix size");
  }
  
  if (this->GetRows() == 1) {
    return (*this)(0, 0);
  }
  if (this->GetRows() == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  }

  double determinant = 0;
  for (size_t i = 0; i < this->GetRows(); ++i) {
    S21Matrix copy = this->DelRow(i, 0);
    double plus = copy.Determinant();
    // + (minor * matrix[i][0] * (-1) ^ (i + 0))
    if (i % 2 == 1) {
      plus *= -1;
    }
    plus *= (*this)(i, 0);
    determinant += plus;
  }

  return determinant;
}


S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(this->GetRows(), this->GetCols());
  
  for (size_t i = 0; i < this->GetRows(); ++i) {
    for (size_t j = 0; j < this->GetCols(); ++j) {
      S21Matrix copy = this->DelRow(i, j);
      double minor = copy.Determinant();
      if ((i + j) % 2 == 1) {
        result.SetElement(i, j, -minor);
      } else {
        result.SetElement(i, j, minor);
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = this->Determinant();

  if (determinant == 0) {
    throw std::logic_error("determinant = 0");
  }
  
  return this->CalcComplements().Transpose() * (1 / determinant);
}

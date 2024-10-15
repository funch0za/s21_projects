#ifndef S21_MATRIX_OPP_H
#define S21_MATRIX_OPP_H

#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <limits>

class S21Matrix final {
 private:
  size_t rows_, cols_;  
  double **matrix_;  
 
 public:
  S21Matrix();
  S21Matrix(const int rows, const int cols); 
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  
  void CheckIndex(long long i, long long j) const;
  S21Matrix DelRow(size_t x, size_t y) const;

  size_t GetRows() const;
  size_t GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);
  void SetElement(int i, int j, double num);  

  bool EqMatrix(const S21Matrix& other) const;
  
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  
  S21Matrix Transpose();

  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix &other) const;

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  const double& operator()(const int i, const int j) const;
    
  ~S21Matrix(); 
};

#endif

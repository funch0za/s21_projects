#include <cstddef>

#include "test_s21_matrix_plus.h"

/*
 * TEST PARAM
 */

TEST(TestConstructor, TestConstructorParam1) {
  EXPECT_ANY_THROW(S21Matrix(-1, 0));
}

TEST(TestConstructor, TestConstructorParam2) {
  EXPECT_ANY_THROW(S21Matrix(-2, -3));
}

TEST(TestConstructor, TestConstructorParam3) {
  EXPECT_ANY_THROW(S21Matrix(0, -100));
}

TEST(TestConstructor, TestConstructorParam4) {
  test_s21_matrix::constructors::param(3, 2);
}

TEST(TestConstructor, TestConstructorParam5) {
  test_s21_matrix::constructors::param(100, 2);
}

TEST(TestConstructor, TestConstructorParam6) {
  test_s21_matrix::constructors::param(32, 98);
}

TEST(TestConstructor, TestConstructorParam7) {
  test_s21_matrix::constructors::param(5, 5);
}

/*
 * TEST COPY
 */

TEST(TestConstructor, TestConstructorCopy1) {
  test_s21_matrix::constructors::copy(3, 5);
}

TEST(TestConstructor, TestConstructorCopy2) {
  test_s21_matrix::constructors::copy(40, 132);
}

TEST(TestConstructor, TestConstructorCopy3) {
  test_s21_matrix::constructors::copy(1, 1);
}

/*
 * TEST MOVE
 */

TEST(TestConstructor, TestConstructorMove1) {
  test_s21_matrix::constructors::move(3, 2);
}

TEST(TestConstructor, TestConstructorMove2) {
  test_s21_matrix::constructors::move(100, 5);
}

TEST(TestConstructor, TestConstructorMove3) {
  test_s21_matrix::constructors::move(3, 222);
}

TEST(TestConstructor, TestConstructorMove4) {
  test_s21_matrix::constructors::move(108, 21);
}

TEST(TestConstructor, TestConstructorMove5) {
  test_s21_matrix::constructors::move(39, 14);
}

/*
 * TEST OPERATOR =
 */

TEST(TestConstructor, TestOperator1) {
  test_s21_matrix::constructors::operator_copy(23, 5);
}

TEST(TestConstructor, TestOperator2) {
  test_s21_matrix::constructors::operator_copy(100, 200);
}

TEST(TestConstructor, TestOperator3) {
  test_s21_matrix::constructors::operator_copy(1, 1);
}

TEST(TestConstructor, TestOperator4) {
  test_s21_matrix::constructors::operator_copy(45, 9);
}

TEST(TestConstructor, TestOperator5) {
  test_s21_matrix::constructors::operator_copy(12, 21);
}

/**
 * Course project for class TEHPC Spring 2022
 *
 * @LICENSE{
 *
 * Copyright 2022 ETH Zurich (class TEHPC Spring 2022)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *}
 */

#ifndef __MATRIX__HH__
#define __MATRIX__HH__

#include "common.hpp"
#include "base_matrix.hpp"
#include "vector.hpp"

template<typename T>
class Matrix : public BaseMatrix<T> {

private:
  using Parent = BaseMatrix<T>;

  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  Matrix() = default;

  Matrix(UInt rows, UInt cols) : Parent() {
    this->resize(rows, cols);
  };

  ~Matrix() = default;

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:

  //! resizing the matrix to given rows and cols
  void resize(UInt rows, UInt cols) {

    Parent::resize(rows, cols);

    //! adapt memory
    UInt size = rows*cols;
    this->storage.resize(size);
  }

  //! operator to access ans assign values 
  //! stored in a column major
  T& operator()(UInt i, UInt j) {
    return this->storage[i + j*this->rows];
  }
  T operator()(UInt i, UInt j) const {
    return this->storage[i + j*this->rows];
  }

  //! operator division by scalar
  Matrix<T>& operator/=(const T& c) {
    std::for_each(this->storage.begin(), this->storage.end(), [&c](T& v) { v /= c; });
    return *this;
  }
  
  //! operator multiplication by scalar
  Matrix<T>& operator*=(const double& c) {
    std::for_each(this->storage.begin(), this->storage.end(), [&c](T& v) { v *= c; });
    return *this;
  }
  
  //! operator multiplication increment by matrix
  Matrix<T>& operator+=(const Matrix<T>& a) {
    this->storage += a.storage;
    return *this;
  }
  
  //! set value to a scalar
  Matrix<T>& operator=(T c) {
    std::for_each(this->storage.begin(), this->storage.end(), [c](T& v) { v = c; });
    return *this;
  }

public:
  //! transpose a matrix
  void transpose(Matrix<T> &);
 
  //! inverse a matrix
  void inverse(Matrix<T> &);

  //! return determinant of matrix
  double determinant();

//private: 
//  void submatrix(Matrix<T> & sub, UInt n, UInt m);

public:
  //! print matrix
  virtual void print(std::ostream& stream) const;

};


/* -------------------------------------------------------------------------- */
/* Separate function definitions */
/* -------------------------------------------------------------------------- */

//! matrix matrix multiplication
template<typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T> & b);

//! double matrix multiplication
template<typename T>
Matrix<T> operator*(const double& c, const Matrix<T> & a);

//! matrix matrix subtraction
template<typename T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T> & b);

//! matrix matrix addition
template<typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T> & b);

//! matrix vector multiplication
template<typename T>
std::vector<T> operator*(const Matrix<T>& a, const std::vector<T> & b);

#include "matrix_inline.hpp"

#endif

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

  // resizing the matrix to given rows and cols
  void resize(UInt rows, UInt cols) {

    Parent::resize(rows, cols);

    // adapt memory
    UInt size = rows*cols;
    this->storage.resize(size);
  }

  // operator to access ans assign values 
  // stored in a column major
  T& operator()(UInt i, UInt j) {
    return this->storage[i + j*this->rows];
  }
  T operator()(UInt i, UInt j) const {
    return this->storage[i + j*this->rows];
  }

  // operator division by scalar
  Matrix<T>& operator/=(const T& c) {
    std::for_each(this->storage.begin(), this->storage.end(), [&c](T& v) { v /= c; });
    return *this;
  }
  
  // operator multiplication by scalar
  Matrix<T>& operator*=(const double& c) {
    std::for_each(this->storage.begin(), this->storage.end(), [&c](T& v) { v *= c; });
    return *this;
  }
  
  // operator multiplication increment by matrix
Matrix<T>& operator+=(const Matrix<T>& a) {
    this->storage += a.storage;
    return *this;
  }
  
  // set value to a scalar
  Matrix<T>& operator=(T c) {
    std::for_each(this->storage.begin(), this->storage.end(), [c](T& v) { v = c; });
    return *this;
  }

public:
  // transpose a matrix
  void transpose(Matrix<T> &);
 
  // inverse a matrix
  void inverse(Matrix<T> &);

  // return determinant of matrix
  double determinant();


public:
  // print matrix
  virtual void print(std::ostream& stream) const;

};


/* -------------------------------------------------------------------------- */
/* Separate function definitions */
/* -------------------------------------------------------------------------- */

// matrix matrix multiplication
template<typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T> & b);

// double matrix multiplication
template<typename T>
Matrix<T> operator*(const double& c, const Matrix<T> & a);

// matrix matrix subtraction
template<typename T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T> & b);

// matrix matrix addition
template<typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T> & b);

// matrix vector multiplication
template<typename T>
std::vector<T> operator*(const Matrix<T>& a, const std::vector<T> & b);

#include "matrix_inline.hpp"

#endif

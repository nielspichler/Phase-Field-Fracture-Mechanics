#ifndef __MATRIX__HH__
#define __MATRIX__HH__

#include <memory>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>   // for setprecision

#include "vector.hpp"

using UInt = unsigned int;


class Matrix {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  Matrix() = default;
  
  Matrix(UInt rows, UInt cols) {
    resize(rows, cols);
  };
    
  ~Matrix() = default;


  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  // accessor to member rows
  UInt nbRows() const { return this->rows; }

  // accessor to member cols
  UInt nbCols() const { return this->cols; }

  // resizing the matrix to given rows and cols
  void resize(UInt rows, UInt cols) {
    this->rows = rows;
    this->cols = cols;
    UInt size = rows*cols;
    storage.resize(size);
  }

  // get the column of a matrix 
  Matrix col(UInt colNb);

  // operator to access ans assign values 
  // stored in a column major
  double& operator()(UInt i, UInt j) {
     return storage[i + j*this->rows];
   }


  // operator division by scalar
  Matrix& operator/=(const double& c) {
    std::for_each(storage.begin(), storage.end(), [&c](double& v) { v /= c; });
    return *this;
  }
  
  // operator multiplication by scalar
  Matrix& operator*=(const double& c) {
    std::for_each(storage.begin(), storage.end(), [&c](double& v) { v *= c; });
    return *this;
  }
  
  // operator multiplication by scalar
  Matrix operator*(const double& c) {
	Matrix a(this->rows, this->cols);
	a.storage = this->storage*c;
    return a;
  }
  
  // operator += increment by matrix
Matrix& operator+=(const Matrix & A) {
	this->storage += A.storage;
    return *this;
  }
  

  // set value to a scalar
  Matrix& operator=(double c) {
    std::for_each(storage.begin(), storage.end(), [c](double& v) { v = c; });
    return *this;
  }


public:
  // transpose a matrix
  void transpose(Matrix &);
 
  // inverse a matrix
  void inverse(Matrix &);

  // return determinant of matrix
  double determinant();

  // return single col matrix as vector
  std::vector<double> toVector()
  {
	assert((this->nbCols()==1)||(this->nbRows()==1));
	return this->storage;
	}

public:
  //! Output to stream
  friend std::ostream& operator<<(std::ostream& stream, const Matrix& _this);

  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:

  
  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
private:
  // number of rows in the matrix
  UInt rows;

  // number of cols in the matrix
  UInt cols;

  // values of matrix stored in a contiguous manner
  std::vector<double> storage;
};


/* -------------------------------------------------------------------------- */
/* Separate function definitions */
/* -------------------------------------------------------------------------- */

// matrix matrix multiplication
Matrix operator*(const Matrix& a, const Matrix & b);

// matrix matrix subtraction
Matrix operator-(const Matrix& a, const Matrix & b);

// matrix matrix addition
Matrix operator+(const Matrix& a, const Matrix & b);

// matrix vector multiplication
std::vector<double> operator*(const Matrix& a, const std::vector<double> & b);


#include "matrix_inline.hpp"

#endif

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

#include "matrix.hpp"


//! matrix matrix multiplication
template<typename T>
inline Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b){
  assert(b.nbRows() == a.nbCols());

  Matrix<T> c(a.nbRows(), b.nbCols());
    
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < b.nbCols(); j++) { // columns of b
      for(UInt k = 0; k < a.nbCols(); k++) { // columns of a
	c(i, j) += a(i, k) * b(k, j);
      }
    }
  }

  return c;
}

//! operator multiplication by scalar
template<typename T>
inline Matrix<T> operator*(const double& c, const Matrix<T> & a) {
	Matrix<T> res(a.nbRows(), a.nbCols());
	for(UInt i=0; i < a.nbRows(); i++) { // rows of a
		for(UInt j=0; j < a.nbCols(); j++) { // columns of a
			res(i, j) = c * a(i, j);
		}
	}
    return res;
  }

//! matrix matrix subtraction
template<typename T>
inline Matrix<T> operator-(Matrix<T>& a, Matrix<T>& b){
  assert(a.nbRows() == b.nbRows() && a.nbCols() == b.nbCols());

  Matrix<T> c(a.nbRows(), a.nbCols());
    
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < a.nbCols(); j++) { // columns of a
      c(i, j) = a(i, j)  -  b(i, j);
      }
    }

  return c;
}


// matrix matrix addition
template<typename T>
inline Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b){
  assert(a.nbRows() == b.nbRows() && a.nbCols() == b.nbCols());

  Matrix<T> c(a.nbRows(), a.nbCols());
    
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < a.nbCols(); j++) { // columns of a
      c(i, j) = a(i, j)  +  b(i, j);
      }
    }
  return c;
}


// matrix vector multiplication
template<typename T>
inline std::vector<T> operator*(Matrix<T>& a, std::vector<T>& b){
  assert(a.nbCols() == b.size());

  std::vector<T> c;
  c.resize(a.nbRows());
      
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < a.nbCols(); j++) { // columns of a
      c[i] += a(i, j)  *  b[j];
      }
    }
  return c;
}

/// standard output stream operator
template<typename T>
inline void Matrix<T>::print(std::ostream& stream) const {
  //Solution:start
  Parent::print(stream);
  //Solution:end
  int print_precision = 2;
  for (UInt i = 0; i < this->rows; ++i) {
    for (UInt j = 0; j < this->cols; ++j) {
      if ((*this)(i, j) >= 0){
	stream << " " ;
      }
      stream << std::fixed << std::setprecision(print_precision) << (*this)(i, j) << " ";
    }
    stream << std::endl;;
  }
}

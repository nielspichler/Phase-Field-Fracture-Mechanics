#include "matrix.hpp"


// matrix matrix multiplication
template<typename T>
inline Matrix<T> operator*(Matrix<T>& a, Matrix<T>& b){
  assert(a.nbRows() == b.nbCols() && b.nbRows() == a.nbCols());

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

// operator multiplication by scalar
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

// matrix matrix subtraction
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
inline Matrix<T> operator+(Matrix<T>& a, Matrix<T>& b){
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
  c.resize(b.size());
      
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

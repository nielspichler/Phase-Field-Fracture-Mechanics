#include "matrix.hpp"


// matrix matrix multiplication
inline Matrix operator*(Matrix& a, Matrix& b){
  assert(a.nbRows() == b.nbCols() && b.nbRows() == a.nbCols());

  Matrix c(a.nbRows(), b.nbCols());
    
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < b.nbCols(); j++) { // columns of b
      for(UInt k = 0; k < a.nbCols(); k++) { // columns of a
	c(i, j) += a(i, k) * b(k, j);
      }
    }
  }

  return c;
}



// matrix matrix subtraction
inline Matrix operator-(Matrix& a, Matrix& b){
  assert(a.nbRows() == b.nbRows() && a.nbCols() == b.nbCols());

  Matrix c(a.nbRows(), a.nbCols());
    
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < a.nbCols(); j++) { // columns of a
      c(i, j) = a(i, j)  -  b(i, j);
      }
    }

  return c;
}


// matrix matrix addition
inline Matrix operator+(Matrix& a, Matrix& b){
  assert(a.nbRows() == b.nbRows() && a.nbCols() == b.nbCols());

  Matrix c(a.nbRows(), a.nbCols());
    
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < a.nbCols(); j++) { // columns of a
      c(i, j) = a(i, j)  +  b(i, j);
      }
    }
  return c;
}


// matrix vector multiplication
inline std::vector<double> operator*(Matrix& a, std::vector<double>& b){
  assert(a.nbCols() == b.size());

  std::vector<double> c;
  c.resize(b.size());
      
  for(UInt i=0; i < a.nbRows(); i++) { // rows of a
    for(UInt j=0; j < a.nbCols(); j++) { // columns of a
      c[i] += a(i, j)  *  b[j];
      }
    }
  return c;
}

  // Addition of 1d matrix and vector
inline std::vector<double> operator+(Matrix& A, std::vector<double>& b){
	assert((A.nbCols()==1)||(A.nbRows()==1));
	assert((A.nbCols()==b.size())||(A.nbRows()==b.size()));
	std::vector<double> c;
	c.resize(b.size());
	if (A.nbCols()==1){
		for(UInt i =0;i<b.size();i++)
			{
				c[i]=b[i] + A(i,0);
			}
		}
	else // nbRows==1 
	{
		for(UInt i =0;i<b.size();i++)
			{
				c[i]=b[i] + A(0,i);
			}
	}
    return c;
  }

/// standard output stream operator
inline std::ostream& operator<<(std::ostream& stream, Matrix& _this) {
  int print_precision = 2;
  for (UInt i = 0; i < _this.nbRows(); ++i) {
    for (UInt j = 0; j < _this.nbCols(); ++j) {
      if (_this(i, j) >= 0){
	stream << " " ;
      }
      stream << std::fixed << std::setprecision(print_precision) << _this(i, j) << " ";
    }
    stream << std::endl;;
  }

  return stream;
}

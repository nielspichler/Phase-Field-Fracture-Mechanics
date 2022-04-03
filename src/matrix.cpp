#include "matrix.hpp"


double Matrix::determinant() {

  assert(this->rows == this->cols);
  
  std::vector<UInt> permutation(this->rows);
  
  for (UInt i=0; i < this->rows; ++i) {
    permutation[i] = i;
  }
  // declare a double 'det_K' to store the determinant of the matrix
  double det_K = 0;
  // do while loop to compute the determinant
  do {
    double n_reorder = 0;
    double product = 1;
    for (UInt i=0; i < this->rows; ++i) {
      product *= (*this)(i, permutation[i]);
      for (UInt j=0; j < i; ++j) {
        if (permutation[j]>permutation[i]) {
          ++n_reorder;
        }
      }
    }
    det_K += std::pow(-1,n_reorder) * product;
  } while(std::next_permutation(permutation.begin(), permutation.end()));

  return det_K;
}


void Matrix::inverse(Matrix & inv) {

  assert(this->rows == this->cols);
  
  inv.resize(this->rows, this->cols);

  double det_K = this->determinant();  
  // check singularity
  assert(det_K != 0);

  Matrix tmp(this->rows-1, this->cols-1);
    
  for (UInt m=0; m < this->rows; ++m) {
    for (UInt n=0; n < this->cols; ++n) { 

      // assign values from 'K' matrix without 'm'th row and 'n'th col to 'tmp'
      UInt idx0 = 0;
      for (UInt i=0; i < this->rows-1; ++i) {
        if (idx0 == m) ++idx0;
        UInt idx1 = 0;
          for (UInt j=0; j < this->cols-1; ++j) {
            if (idx1 == n) ++idx1;
            tmp(i, j) = (*this)(idx0, idx1);
            ++idx1;
          }     
        ++idx0;
      } 

      // compute determinant of the tmp matrix
      double det_tmp = tmp.determinant();
      // compute the (n,m) entry of adjugate matrix and inverse matrix
      inv(n, m) = std::pow(-1,m+n) * det_tmp / det_K;
    }
  }
}


void Matrix::transpose(Matrix & a) {
  a.resize(this->cols, this->rows);
  
  for (UInt i=0; i < this->rows; ++i) {
    for (UInt j=0; j < this->cols; ++j) {
      a(j, i) = (*this)(i, j); 
    }
  }
}


Matrix Matrix::col(UInt colNb){
	assert(colNb<cols);
	Matrix a(this->rows,1);
	
	for (UInt i=0; i < this->rows; ++i){
	a(i, 0) = (*this)(i, colNb);
	}
	return a;
	}

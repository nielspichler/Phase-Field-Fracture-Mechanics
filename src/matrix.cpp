#include "matrix.hpp"

/* -------------------------------------------------------------------------- */


template<typename T>
double Matrix<T>::determinant() {

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
		det_K += pow(-1,n_reorder) * product;
	} while(std::next_permutation(permutation.begin(), permutation.end()));
  return det_K;
}

/*
template<typename T>
double Matrix<T>::determinant(){
	assert(this->rows == this->cols);
	double det=0.0;
	if (this->rows == 1){
		return (*this)(0,0);
		}
	
	Matrix<T> A_sub(this->rows-1, this->rows-1);
	
	for (UInt i=0; i<this->rows; i++){
		this->submatrix(A_sub, i, 0);
		det += pow(-1, i) * (*this)(i, 0) * A_sub.determinant();
		}
	
	return det;
	}
*/

template<typename T>
void Matrix<T>::submatrix(Matrix<T> & sub, UInt n, UInt m){
	
	UInt a=0, b=0;
	
	for (UInt i=0; i<this->rows; i++){
		if (i==n) continue;
		b=0;
		for (UInt j=0; j<this->cols; j++){
			if (j==m) continue;
			sub(a, b) = (*this)(i, j);
			b++;
			}
		a++;
		}
		
	}

/* -------------------------------------------------------------------------- */
template<typename T>
void Matrix<T>::inverse(Matrix<T> & inv) {

  assert(this->rows == this->cols);
  
  inv.resize(this->rows, this->cols);

  double det_K = this->determinant();  
  // check singularity
  //assert(det_K != 0); // assertion never tripped ! 
  assert((1e-6<det_K)||(-1e-6>det_K));

  Matrix<T> tmp(this->rows-1, this->cols-1);
    
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

/* -------------------------------------------------------------------------- */
template<typename T>
void Matrix<T>::transpose(Matrix<T> & a) {
  a.resize(this->cols, this->rows);
  
  for (UInt i=0; i < this->rows; ++i) {
    for (UInt j=0; j < this->cols; ++j) {
      a(j, i) = (*this)(i, j); 
    }
  }
}


template<typename T>

void Matrix<T>::permute_cols(UInt i, UInt j){
	
	std::vector<T> col_tmp(this->cols);
	
	std::copy_n(this->storage.begin()+i*this->rows, this->cols, col_tmp.begin()); // col_tmp = col_i
	
	std::swap_ranges(this->storage.begin()+j*this->rows, this->storage.begin()+(j+1)*this->rows, col_tmp.begin()); //we swap col_j and col_tmp
	
	std::swap_ranges(this->storage.begin()+i*this->rows, this->storage.begin()+(i+1)*this->rows, col_tmp.begin()); //we swap col_i and col_tmp
	
	}

template<typename T>
void Matrix<T>::permute_rows(UInt i, UInt j){
	
	double tmp;
	
	for (UInt k=0; k<this->rows; k++){
		
		tmp = this->storage[i + k*this->cols];
		this->storage[i + k*this->rows] = this->storage[j + k*this->rows];
		this->storage[j + k*this->rows] = tmp;
		
		}
	
	}

template class Matrix<UInt>;
template class Matrix<double>;


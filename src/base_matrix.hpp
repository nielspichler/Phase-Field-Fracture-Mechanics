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

#ifndef __BASE_MATRIX__HH__
#define __BASE_MATRIX__HH__

//Solution:start
#include <iostream>
#include <vector>
//Solution:end

#include "common.hpp"

template<typename T>
class BaseMatrix; // forward declare to make function declaration possible
 
template<typename T> // declaration
std::ostream& operator<<(std::ostream&, const BaseMatrix<T>&);

template<typename T>
class BaseMatrix {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  //Solution:start
  BaseMatrix() = default;
  
  BaseMatrix(UInt rows, UInt cols) {
    resize(rows, cols);
  };
    
  virtual ~BaseMatrix() = default;
//Solution:end

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  //Solution:start
  //! sets size of matrix but does not adapt the storage memory (child class)
  virtual void resize(UInt rows, UInt cols) {
    this->rows = rows;
    this->cols = cols;
  }

  //! operator to access and assign values 
  //! stored in a column major
  virtual T& operator()(UInt i, UInt j) = 0;

  //! operator to access only values
  virtual T operator()(UInt i, UInt j) const = 0;
  //Solution:end
  
  //! set value to a scalar
  virtual BaseMatrix<T>& operator=(T c) = 0;
  
public:
  //Solution:start
  //! Output to stream
  friend std::ostream& operator<< <> (std::ostream& stream, const BaseMatrix<T>& _this);
  //Solution:end
  
  // print matrix
  virtual void print(std::ostream& stream) const {
    stream << "size         = " << this->size() << std::endl;
    stream << "storage size = " << this->storageSize() << std::endl;
  }
  
  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:
  //Solution:start
  //! accessor to member rows
  UInt nbRows() const { return this->rows; }

  //! accessor to member cols
  UInt nbCols() const { return this->cols; }
  //Solution:end
  
  //! size of matrix
  UInt size() const { return this->rows*this->cols; }
  
  //! get information about size of storage
  UInt storageSize() const { return this->storage.size(); }

  //! access storage
  std::vector<double> & getStorage() { return this->storage; }
  
	/*!
	* @param row_indices
	* @param col_indices
	* @param valued
	* Sets the row index, col indes and value vectors to express the matrox as a sparse matrix
	* Ideally should be defined in base_matrix.cpp but it does not exist
	*/
  void getSparseStorage(std::vector<UInt> & row_indices, std::vector<UInt> & col_indices, std::vector<double> & values){
	  for (UInt i=0; i < this->rows; ++i) {
		  for (UInt j=0; j<this->cols; j++) {
			  double tmp_val = storage[i + j*this->rows];
			  if (tmp_val !=0.0) {
				  row_indices.push_back(i);
				  col_indices.push_back(j);
				  values.push_back(tmp_val);
				  }
			  }
		  }
	  }
  
  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
protected:
  //Solution:start
  //! number of rows in the matrix
  UInt rows;

  //! number of cols in the matrix
  UInt cols;

  //! values of matrix stored in a contiguous manner
  std::vector<T> storage;
  //Solution:end
};



/* -------------------------------------------------------------------------- */
/* Separate function definitions */
/* -------------------------------------------------------------------------- */

//Solution:start
/// standard output stream operator
template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const BaseMatrix<T>& _this) {
  _this.print(stream);
  return stream;
}
//Solution:end

#endif

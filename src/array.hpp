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


#ifndef __ARRAY__HH__
#define __ARRAY__HH__

#include "common.hpp"
#include "base_matrix.hpp"
#include "vector.hpp"

template<typename T>
class Array : public BaseMatrix<T> {

private:
  using Parent = BaseMatrix<T>;

  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  Array() = default;

  Array(UInt rows, UInt cols) : Parent() {
    this->resize(rows, cols);
  };

  ~Array() = default;

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
  //! stored in a row major
  T& operator()(UInt i, UInt j) {
    return this->storage[i*this->cols + j];
  }
  T operator()(UInt i, UInt j) const {
    return this->storage[i*this->cols + j];
  }
  
  //! gets the column of the array
  std::vector<T> operator()(UInt i) const {
	std::vector<T> res;
	res.resize(this->storage.size()/this->cols);
	for (UInt j = 0; j<res.size(); j++){
		res[j] = this->storage[j*this->cols + i];
		}
    return res;
  }

  //! set value to a scalar
  Array<T>& operator=(T c) {
    std::for_each(this->storage.begin(), this->storage.end(), [c](T& v) { v = c; });
    return *this;
  }

public:
  //! print array
  virtual void print(std::ostream& stream) const;
};


/* -------------------------------------------------------------------------- */
/* Separate function definitions */
/* -------------------------------------------------------------------------- */

#include "array_inline.hpp"

#endif

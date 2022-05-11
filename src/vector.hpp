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

#ifndef __VECTOR__HH__
#define __VECTOR__HH__

#include "common.hpp"
#include <vector>

using UInt = unsigned int;


//! printing std::vector
template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const std::vector<T>& _this) {
int print_precision = 2;
  for (UInt i = 0; i < _this.size(); ++i) {
    if (_this[i] >= 0){
	stream << " " ;
    }
    stream << std::fixed << std::setprecision(print_precision) << _this[i] << " " << std::endl;
  }
    
  return stream;
}


//! vector vector addition
template<typename T>
inline std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {

  assert(a.size() == b.size());
  
  std::vector<T> c;
  c.resize(a.size());
  
  for (UInt i = 0; i < a.size(); ++i) {
    c[i] = a[i]+b[i];
  }

  return c;
}


//! vector vector subtraction
template<typename T>
inline std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b) {

  assert(a.size() == b.size());
  
  std::vector<T> c;
  c.resize(a.size());
  
  for (UInt i = 0; i < a.size(); ++i) {
    c[i] = a[i]-b[i];
  }

  return c;
}


//! vector multiplication by scalar
template<typename T>
inline std::vector<T> operator*(const std::vector<T>& a, double b) {
  
  std::vector<T> c;
  c.resize(a.size());
  
  for (UInt i = 0; i < a.size(); ++i) {
    c[i] = a[i]*b;
  }

  return c;
}


//! dot product
template<typename T>
inline double operator*(const std::vector<T>& a, const std::vector<T>& b) {
  assert(a.size() == b.size());

  double product = 0;
  for (UInt i = 0; i < a.size(); ++i) {
    product += a[i]*b[i];
  }

  return product;
}


//! vector +=
template<typename T>
inline void operator+=(std::vector<T> &v1, const std::vector<T> &v2) {
	
	assert(v1.size() == v2.size());
	
	for (UInt i = 0; i<v1.size(); i++){
		v1[i] += v2[i];
	}
}

#endif

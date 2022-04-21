#ifndef __VECTOR__HH__
#define __VECTOR__HH__

#include "common.hpp"
#include <vector>

using UInt = unsigned int;


// printing std::vector
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


// vector vector addition
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


// vector vector subtraction
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


// vector multiplication by scalar
template<typename T>
inline std::vector<T> operator*(const std::vector<T>& a, double b) {
  
  std::vector<T> c;
  c.resize(a.size());
  
  for (UInt i = 0; i < a.size(); ++i) {
    c[i] = a[i]*b;
  }

  return c;
}


// dot product
template<typename T>
inline double operator*(const std::vector<T>& a, const std::vector<T>& b) {
  assert(a.size() == b.size());

  double product = 0;
  for (UInt i = 0; i < a.size(); ++i) {
    product += a[i]*b[i];
  }

  return product;
}


// vector +=
template<typename T>
inline void operator+=(std::vector<T> &v1, const std::vector<T> &v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
}

#endif

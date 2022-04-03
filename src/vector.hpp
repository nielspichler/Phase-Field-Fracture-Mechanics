#ifndef __VECTOR__HH__
#define __VECTOR__HH__

#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>   // for setprecision


using UInt = unsigned int;


// printing std::vector
inline std::ostream& operator<<(std::ostream& stream, const std::vector<double>& _this) {
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
inline std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b) {

  assert(a.size() == b.size());
  
  std::vector<double> c;
  c.resize(a.size());
  
  for (UInt i = 0; i < a.size(); ++i) {
    c[i] = a[i]+b[i];
  }

  return c;
}

// vector vector increment addition
inline std::vector<double> operator+=( std::vector<double>& a, const std::vector<double>& b) {

  assert(a.size() == b.size());

  for (UInt i = 0; i < b.size(); ++i) {
    a[i] += b[i];
  }

  return a;
}


// vector vector subtraction
inline std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b) {

  assert(a.size() == b.size());
  
  std::vector<double> c;
  c.resize(a.size());
  
  for (UInt i = 0; i < a.size(); ++i) {
    c[i] = a[i]-b[i];
  }

  return c;
}


// vector multiplication by scalar
inline std::vector<double> operator*(const std::vector<double>& a, double b) {
  
  std::vector<double> c;
  c.resize(a.size());
  
  for (UInt i = 0; i < a.size(); ++i) {
    c[i] = a[i]*b;
  }

  return c;
}


// dot product
inline double operator*(const std::vector<double>& a, const std::vector<double>& b) {
  assert(a.size() == b.size());

  double product = 0;
  for (UInt i = 0; i < a.size(); ++i) {
    product += a[i]*b[i];
  }

  return product;
}

#endif

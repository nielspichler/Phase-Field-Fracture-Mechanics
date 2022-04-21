#include "array.hpp"

/// standard output stream operator
template<typename T>
inline void Array<T>::print(std::ostream& stream) const {
  Parent::print(stream);
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

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

  // resizing the matrix to given rows and cols
  void resize(UInt rows, UInt cols) {

    Parent::resize(rows, cols);

    // adapt memory
    UInt size = rows*cols;
    this->storage.resize(size);
  }

  // operator to access ans assign values 
  // stored in a row major
  T& operator()(UInt i, UInt j) {
    return this->storage[i*this->cols + j];
  }
  T operator()(UInt i, UInt j) const {
    return this->storage[i*this->cols + j];
  }

  // set value to a scalar
  Array<T>& operator=(T c) {
    std::for_each(this->storage.begin(), this->storage.end(), [c](T& v) { v = c; });
    return *this;
  }

public:
  // print array
  virtual void print(std::ostream& stream) const;
};


/* -------------------------------------------------------------------------- */
/* Separate function definitions */
/* -------------------------------------------------------------------------- */

#include "array_inline.hpp"

#endif

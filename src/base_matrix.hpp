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
  // sets size of matrix but does not adapt the storage memory (child class)
  virtual void resize(UInt rows, UInt cols) {
    this->rows = rows;
    this->cols = cols;
  }

  // operator to access and assign values 
  // stored in a column major
  virtual T& operator()(UInt i, UInt j) = 0;

  // operator to access only values
  virtual T operator()(UInt i, UInt j) const = 0;
  //Solution:end
  
  // set value to a scalar
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
  // accessor to member rows
  UInt nbRows() const { return this->rows; }

  // accessor to member cols
  UInt nbCols() const { return this->cols; }
  //Solution:end
  
  // size of matrix
  UInt size() const { return this->rows*this->cols; }
  
  // get information about size of storage
  UInt storageSize() const { return this->storage.size(); }

  // access storage
  std::vector<double> & getStorage() { return this->storage; }
  
  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
protected:
  //Solution:start
  // number of rows in the matrix
  UInt rows;

  // number of cols in the matrix
  UInt cols;

  // values of matrix stored in a contiguous manner
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

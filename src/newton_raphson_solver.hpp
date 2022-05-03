#ifndef __NRSOLVER__HH__
#define __NRSOLVER__HH__

#include <string>
#include <vector>

#include "common.hpp"
#include "matrix.hpp"
#include "vector.hpp" //for vector operator overloading

#include "matrix.hpp"


//Solution:start
class NRsolver {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  NRsolver() : NRsolver(100, 1e-6) {};

  NRsolver(int max_iter,double epsilon) {
	  
  std::cout << "init NRsolver with "
  << "max_iter = " << max_iter << " and "
  << "epsilon = " << epsilon << std::endl;

  this->max_iter = max_iter;
  this->epsilon = epsilon;  
	};

  ~NRsolver() = default;
  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public: 
  // solve A*x = b
  void solve(std::shared_ptr<BaseMatrix<double> > A,
	     const std::vector<double>& b, std::vector<double>& x);

private:
  // compute residual f = A * x - b
  void myFun(Matrix<double> & A,
	     const std::vector<double>& b, std::vector<double>& x,
	     std::vector<double>& f);
  
  // compute f' = A
  void myFunDerivative(const Matrix<double>& A,
		       Matrix<double>& dfdx);
  
  void update(std::vector<double>& x_next, std::vector<double>& x_prev,  
	      Matrix<double>& dfdx_inv, std::vector<double>& f);

  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:
  void printInfo() {
    std::cout << "Nonlinear solver:" << "\n";
    std::cout << "  maximum number of iterations: " << this->max_iter << "\n";
    std::cout << "  tolerance: " << std::scientific << this->epsilon << std::endl;
    std::cout << "  method: newton raphson method" << std::endl;
  }

  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
private:
  // user-prescribed maximum number of iterations
  int max_iter;

  // user-prescribed epsilon
  double epsilon;  
};

#endif

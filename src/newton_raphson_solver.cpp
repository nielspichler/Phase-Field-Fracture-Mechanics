#include "newton_raphson_solver.hpp"

void NRsolver::solve(std::shared_ptr<BaseMatrix<double> > Ap,
		     const std::vector<double>& b, std::vector<double>& x) {

  Matrix<double> A = dynamic_cast<Matrix<double>&>(*Ap);
  
  unsigned int size = b.size();

  //initialize x_prev with "x"
  std::vector<double> x_prev(x);

  // create vectors with size "size"
  std::vector<double> x_next(size);
  std::vector<double> f(size);

  Matrix<double> dfdx(size,size);    
  Matrix<double> dfdx_inv(size,size);

  #ifdef TEHPC_VERBOSE
  //print  x[0] to terminal
  std::cout << "initial guess " << std::endl;
  std::cout << GET_VARIABLE_NAME(x) <<"[" << 0 << "] = " << std::endl;
  std::cout << x << std::endl;

  // print this->epsilon
  std::cout << "epsilon   =  " << this->epsilon << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  #endif /* THEPC_VERBOSE */
  //-------------------------------iterate ---------------------------------------
  for(int i = 0; i < this->max_iter; i++){

    // compute residual f = A * x_prev - b
    myFun(A, b, x_prev,f);

    // compute norm of residual f
    double r_norm = std::sqrt(f * f);

    if (r_norm < this->epsilon) {
	  #ifdef TEHPC_VERBOSE
      std::cout << " Converged" << std::endl;

      // print x on each iteration
      std::cout << GET_VARIABLE_NAME(x_next) <<"[" << i+1 << "] = " << std::endl;
      std::cout << x_next << std::endl;

      // print r
      std::cout << GET_VARIABLE_NAME(f) <<"[" << i+1 << "] = " << std::endl;
      std::cout << f << std::endl;
      #endif /* THEPC_VERBOSE */

      // assign updated values to x
      x = x_next;
      
      return;
    }

    // compute values of first derivative of function f(x) = A
    myFunDerivative(A, dfdx);

    // get inverse Jacobian matrix
    dfdx.inverse(dfdx_inv);

    // update x with x_i+1 = x_i - f'(x_i)^(-1)*f(x_i)
    update(x_next,x_prev,dfdx_inv, f);
  }
  
  // assign updated values to x
  x = x_next;

  
  std::cout << "Convergence not reached" << std::endl;
  std::cout << "Error: Max number of iterations exceeded" << std::endl;
  #ifdef TEHPC_VERBOSE
  // print final x
  std::cout << GET_VARIABLE_NAME(x_next) <<"[" << this->max_iter << "] = " << std::endl;
  std::cout << x_next << std::endl;

  // print final absolute value of delta
  std::cout << GET_VARIABLE_NAME(f) <<"[" << this->max_iter << "] = " << std::endl;
  std::cout << f << std::endl;
  #endif /* THEPC_VERBOSE */
  

  return;
}


void NRsolver::myFun(Matrix<double>& A,
		     const std::vector<double>& b, std::vector<double>& x, 
		     std::vector<double>& f){
  // f(x) = A*x - b;
  f = A * x - b;
}

// dfdx = A;
void NRsolver::myFunDerivative(const Matrix<double>& A, Matrix<double>& dfdx) {
  dfdx = A;
}

// update x_next and x_prev.
void NRsolver::update(std::vector<double>& x_next, std::vector<double>& x_prev, 
                      Matrix<double>& dfdx_inv, std::vector<double>& f) {
  // update next step: x_next = x_prev - dfdx_inv * f;
  x_next = x_prev - dfdx_inv * f;
  
  // update prev step: x_prev = x_next;
  x_prev =  x_next;
}



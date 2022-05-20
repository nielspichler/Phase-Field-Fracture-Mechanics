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
#ifndef __NRSOLVER__HH__
#define __NRSOLVER__HH__

//SP:#include <string>
//SP:#include <vector>

//SP:#include "common.hpp"
//SP:#include "matrix.hpp"
//SP:#include "vector.hpp" //for vector operator overloading

#include "matrix.hpp"

//Solution:start
#include "nonlinear_solver.hpp"
//Solution:end

//Solution:start
class NRsolver : public NLsolver {
//Solution:end
//SP:class NRsolver {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  NRsolver() : NRsolver(100, 1e-6) {};

  //Solution:start
  NRsolver(int max_iter,double epsilon) : NLsolver(max_iter,epsilon) {};
  //Solution:end
  //SP:NRsolver(int max_iter,double epsilon) {
    //SP:this->max_iter = max_iter;
    //SP:this->epsilon = epsilon;  
  //SP:};

  ~NRsolver() = default;
  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public: 
  // solve A*x = b
  void solve(std::shared_ptr<BaseMatrix<double> > A,
	     const std::vector<double>& b, std::vector<double>& x);

private:
  //! compute residual f = A * x - b
  void myFun(Matrix<double> & A,
	     const std::vector<double>& b, std::vector<double>& x,
	     std::vector<double>& f);
  
  //! compute f' = A
  void myFunDerivative(const Matrix<double>& A,
		       Matrix<double>& dfdx);
  
  void update(std::vector<double>& x_next, std::vector<double>& x_prev,  
	      Matrix<double>& dfdx_inv, std::vector<double>& f);

  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:
  void printInfo() {
    //Solution:start
    NLsolver::printInfo();
    //Solution:end
    //SP:std::cout << "Nonlinear solver:" << "\n";
    //SP:std::cout << "  maximum number of iterations: " << this->max_iter << "\n";
    //SP:std::cout << "  tolerance: " << std::scientific << this->epsilon << std::endl;
    std::cout << "  method: newton raphson method" << std::endl;
  }

  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
private:
  //SP:// user-prescribed maximum number of iterations
  //SP:int max_iter;

  //SP:// user-prescribed epsilon
  //SP:double epsilon;  
};

#endif

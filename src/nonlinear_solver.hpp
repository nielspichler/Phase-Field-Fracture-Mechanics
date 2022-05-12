
/**
 * Course project for class TEHPC Spring 2022
 *
 * @brief Base class for various non-linear solvers
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
 

#ifndef __NONLINEAR_SOLVER__HH__
#define __NONLINEAR_SOLVER__HH__

/* -------------------------------------------------------------------------- */
#include <string>
#include <vector>
#include <memory>

#include "common.hpp"
#include "base_matrix.hpp"
#include "vector.hpp" //for vector operator overloading
/* -------------------------------------------------------------------------- */

class NLsolver {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
  
public:
  NLsolver() : NLsolver(100, 1e-6) {};

  NLsolver(int max_iter,double epsilon) {
#ifdef TEHPC_VERBOSE
    std::cout << "init NLsolver with "
	      << "max_iter = " << max_iter << " and "
	      << "epsilon = " << epsilon << std::endl;
#endif /* THEPC_VERBOSE */
    this->max_iter = max_iter;
    this->epsilon = epsilon;  
  };

  virtual ~NLsolver() = default;
  
  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
  
public: 
  //! solves A*x = b
  virtual void solve(std::shared_ptr<BaseMatrix<double> > A,
		     const std::vector<double>& b, 
		     std::vector<double>& x) = 0;
  
  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:
  //! prints the information about the non-linear solver
  virtual void printInfo() {
    std::cout << "Nonlinear solver:" << "\n";
    std::cout << "  maximum number of iterations: " << this->max_iter << "\n";
    std::cout << "  tolerance: " << std::scientific << this->epsilon << std::endl;
  }

  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
  
protected:
  //! user-prescribed maximum number of iterations
  int max_iter;

  //! user-prescribed epsilon for tolerance check
  double epsilon;  
 
};
#endif

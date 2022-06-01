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
 
#ifndef __ARMADILLOSOLVER__HH__
#define __ARMADILLOSOLVER__HH__

#include "nonlinear_solver.hpp" 
#include <armadillo>

class ArmadilloSolver : public NLsolver {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  ArmadilloSolver() : NLsolver(0, 0) {};

  ~ArmadilloSolver() = default;
  
  ArmadilloSolver(int max_iter,double epsilon) : NLsolver(max_iter,epsilon) {};

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public: 
  // solve A*x = b
  void solve(std::shared_ptr<BaseMatrix<double> > A,
	     const std::vector<double>& b, std::vector<double>& x);

  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:
  void printInfo() {
    NLsolver::printInfo();
    std::cout << "  method: armadillo" << std::endl;
  }

  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
private:
};

#endif

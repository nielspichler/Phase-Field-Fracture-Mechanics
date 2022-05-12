/*
 * lu_solver.hpp
 * 
 * Copyright 2022 student <student@tehpc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef LU_SOLVER_HPP
#define LU_SOLVER_HPP


#include <string>
#include <vector>

#include "common.hpp"
#include "matrix.hpp"
#include "vector.hpp" //for vector operator overloading
#include "nonlinear_solver.hpp"
#include "matrix.hpp"


class LU_solver : public NLsolver 
{
	public:
		LU_solver() : NLsolver(100, 1e-6) {};
		
		LU_solver(int max_iter,double epsilon) : NLsolver(max_iter,epsilon) {};
		
		void solve(std::shared_ptr<BaseMatrix<double> > A, const std::vector<double>& b, std::vector<double>& x);
		
		void LUPDecompose(Matrix<double>& A, std::vector<int>& P);
		
		void LUPSolve(Matrix<double>& A, std::vector<int>& P, const std::vector<double>& b, std::vector<double>& x);
		
	private:
		/* add your private declarations */
};

#endif /* LU_SOLVER_HPP */ 

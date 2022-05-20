/*
 * copied and adapted from wikipedia
 * https://en.wikipedia.org/wiki/LU_decomposition
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
	/*!
	 * Default constructor for the solver
	 */
		LU_solver() : NLsolver(100, 1e-6) {};
	/*!
	 * @param max_iter useless in this case
	 * @param epsilon tolerance to check if the matrix is degenerate
	 * Constructor for the solver
	 */
		LU_solver(int max_iter,double epsilon) : NLsolver(max_iter,epsilon) {};
	/*!
	 * @param A pointer to a BaseMatrix
	 * @param b vector of residues
	 * @param x vector of unknowns
	 * Will solve A*x=b using LU factorization
	 */
		void solve(std::shared_ptr<BaseMatrix<double> > A, const std::vector<double>& b, std::vector<double>& x);
	/*!
	 * @param A Matrix to decompose
	 * @param P vector of permutations
	 * Will perform LU factorization of A
	 */
		void LUPDecompose(Matrix<double>& A, std::vector<int>& P);
	/*!
	 * @param A decomposed matrix using LUPDecompose() method
	 * @param P vector of permutations filled in LUPDecompose() method
	 * @param b vector of residues
	 * @param x vector of unknowns
	 * Solves LUx = b
	 */
		void LUPSolve(Matrix<double>& A, std::vector<int>& P, const std::vector<double>& b, std::vector<double>& x);
	
	/*!
	 * @param A decomposed matrix using LUPDecompose() method
	 * @param P vector of permutations filled in LUPDecompose() method
	 * returns determinant of A
	 */
	double LUPDeterminant(Matrix<double>& A, std::vector<int>& P);
	
	private:
		/* add your private declarations */
};

#endif /* LU_SOLVER_HPP */ 

#include "armadillo_solver.hpp"


/* -------------------------------------------------------------------------- */
void ArmadilloSolver::solve(std::shared_ptr<BaseMatrix<double> > Ap,
			    const std::vector<double>& b,
			    std::vector<double>& x){

	if (x.size()<100){ // dense solver
		
		//std::cout << "Dense solver" << std::endl;
		
		arma::mat Aa(Ap->getStorage().data(), Ap->nbRows(), Ap->nbCols());
		arma::vec ba(b);
		arma::vec xa(x);
		arma::solve(xa, Aa, ba, arma::solve_opts::fast); 
		
		x = arma::conv_to<std::vector<double>> ::from(xa);
		
		}
	else{ // sparse solver
		std::vector<UInt> row_indices; 
		std::vector<UInt> col_indices; 
		std::vector<double> values;
		
		Ap->getSparseStorage(row_indices, col_indices, values);
		
		arma::uvec row_indices_a = arma::conv_to<arma::uvec>::from(row_indices);
		arma::uvec col_indices_a = arma::conv_to<arma::uvec>::from(col_indices);
		
		arma::vec values_a(values);
		
		arma::umat locations_a = arma::join_cols(row_indices_a.as_row(), col_indices_a.as_row());
		
		//std::cout << "size of row_indices_a: " << arma::size(row_indices_a) << std::endl;
		//std::cout << "size of col_indices_a: " << arma::size(col_indices_a) << std::endl;
		//std::cout << "size of locations_a: " << arma::size(locations_a) << std::endl;
		
		arma::sp_mat Aa(locations_a, values_a);
		
		arma::vec ba(b);
		arma::vec xa(x);
		arma::spsolve(xa, Aa, ba);
		
		x = arma::conv_to<std::vector<double>> ::from(xa);
		}

}

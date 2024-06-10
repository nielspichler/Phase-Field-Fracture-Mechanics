#include "armadillo_solver.hpp"


/* -------------------------------------------------------------------------- */
void ArmadilloSolver::solve(std::shared_ptr<BaseMatrix<double> > Ap,
			    const std::vector<double>& b,
			    std::vector<double>& x){


  arma::mat Aa(Ap->getStorage().data(), Ap->nbRows(), Ap->nbCols());
  arma::vec ba(b);
  arma::vec xa(x);

  //arma::solve(xa, Aa, ba);
  
  arma::solve(xa, Aa, ba, arma::solve_opts::fast); // with this option the code is a bit faster

  x = arma::conv_to<std::vector<double>> ::from(xa);


}

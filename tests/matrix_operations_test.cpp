#include "model.hpp"
#include "matrix.hpp"
#include <string>
#include <fstream>
#include <iostream> // print to console (cout)
#include "test_tools.hpp"



int main(/*int argc, char *argv[]*/){
	
	Matrix<double> M(3,3);
	
	M(0,0) = 1; M(0,1) = 2; M(0,2) = 3; 
	
	M(1,0) = 4; M(1,1) = 5; M(1,2) = 6; 
	
	M(2,0) = 7; M(2,1) = 8; M(2,2) = 9; 
	
	std::cout<<M;
	
	M.permute_cols(0,1);
	
	std::cout<<M;
	
	M.permute_rows(0,1);
	
	std::cout<<M;
	
	Matrix<double> M_true (3,3);

	M_true(0,0) = 5; M_true(0,1) = 4; M_true(0,2) = 6; 
	
	M_true(1,0) = 2; M_true(1,1) = 1; M_true(1,2) = 3; 
	
	M_true(2,0) = 8; M_true(2,1) = 7; M_true(2,2) = 9; 

	Test_tools test;
	test.test_matching_matrices(3, 1e-8, M, M_true);
	test.test_results();
	

	}

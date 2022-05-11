

#include "test_tools.hpp"

Test_tools::Test_tools(){
	success = true;
	}

void Test_tools::test_matching_matrices(int size, double tol, Matrix<double> & K_1, BaseMatrix<double> & K_2)
{
	for (int i = 0; i<size;i++){
		for (int j = 0; j<size; j++){
			if(abs(K_1(i,j)-K_2(i,j))>tol){this->success = false;}
			}
		}
	if (this->success == false){std::cout<<"Test failed !"<< std::endl;}
	}

void Test_tools::test_matching_matrices_LT(int size, double tol, Matrix<double> & K_1, BaseMatrix<double> & K_2)
{
	for (int i = 0; i<size;i++){
		for (int j = 0; j<i+1; j++){
			if(abs(K_1(i,j)-K_2(i,j))>tol){this->success = false;std::cout <<i<<"\n"<<j;}
			}
		}
	if (this->success == false){std::cout<<"Test failed !"<< std::endl;}
	}

void Test_tools::test_matching_vectors(int size, double tol, std::vector<double> & v_1, std::vector<double> & v_2)
{
	for (int i = 0; i<size;i++){
		if(abs(v_1[i]-v_2[i])>tol){this->success = false;}
		}
	if (this->success == false){std::cout<<"Test failed !"<< std::endl;}
	}




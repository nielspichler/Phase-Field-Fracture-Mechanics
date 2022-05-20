#include "model.hpp"
#include "matrix.hpp"
#include <string>
#include <fstream>
#include <iostream> // print to console (cout)
#include "lu_solver.hpp"
#include "newton_raphson_solver.hpp"
#include "test_tools.hpp"

void test_system_by_size(int size)
{
	double tol = 1e-10;
	Test_tools test; // initialize a test object
	std::shared_ptr<BaseMatrix<double> > A;
	A = std::shared_ptr<BaseMatrix<double> >(new Matrix<double>(size, size));
	//(*A).resize(4,4);
	for (int i=0; i<size;i++){
		(*A)(i,i)=1.0;
		}
	
	std::vector<double> b(size);
		for (int i=0;i<size;i++){
		b[i] = rand() * 5.0-10.0;
	}
	
	std::vector<double> x_1(size);
	std::vector<double> x_2(size);
	
	std::shared_ptr<LU_solver> solver_1;
	solver_1 = std::make_shared<LU_solver>(500, 1e-6);
	
	std::shared_ptr<NRsolver> solver_2;
	solver_2 = std::make_shared<NRsolver>(500, 1e-6);
	
	//std::cout<<"A = \n"<<(*A);
	
	solver_1->solve(A, b, x_1);
	std::cout<<"A is identity, test if x=b, LU: "<< std::endl;
	test.test_matching_vectors(size, tol, b, x_1);
	test.test_results();
	
	solver_2->solve(A, b, x_2);
	std::cout<<"A is identity, test if x=b, NR: "<< std::endl;
	test.test_matching_vectors(size, tol, b, x_2);
	test.test_results();
	//std::cout<<b;
	//std::cout<<x_1;
	//std::cout<<x_2;
	// randomly fill a now
	
	do{
	for (int i=0;i<size;i++){
		for (int j=0; j<size;j++){
			(*A)(i,j) = rand() * 5.0-10.0;
			}
	}
	}while (dynamic_cast<Matrix<double>&>(*A).determinant()==0);// if by any chance the random A matrix is singular
	
	solver_1->solve(A, b, x_1);
	solver_2->solve(A, b, x_2);
	std::cout<<"A is random, test if x_LU=x_NR: "<< std::endl;
	test.test_matching_vectors(size, tol, x_1, x_2);
	test.test_results();


	}

int main(/*int argc, char *argv[]*/){
	
	std::cout<<"size = 4\n";
	test_system_by_size(4);
	std::cout<<"size = 5\n";
	test_system_by_size(5);
	std::cout<<"size = 6\n";
	test_system_by_size(6);
	
	
	}

#include "model.hpp"
#include "matrix.hpp"
#include "test_tools.hpp"

#include <string>
#include <fstream>
#include <iostream> // print to console (cout)


int main(/*int argc, char *argv[]*/){
	
	// initial preparations
	
	double tol = 0.00001;
	double tol_K = 1.;
	
	std::vector<double> v_4_0(4);
	std::fill(v_4_0.begin(), v_4_0.end(), 0.);
	
	std::vector<double> v_8_0(8);
	std::fill(v_8_0.begin(), v_8_0.end(), 0.);
	
	Matrix<double> M_8_0(8,8);
	M_8_0 = 0;
	
	Test_tools test; // initialize a test object
	
	
	std::string file_name = "./../../examples/input_paper.inp";
	Model model(file_name);
	
	// at a given timestep we get from the previous timestep some values the phase and the history and the displacement
	
	Array<double> displacement(4,2);
	displacement = 0;
	std::vector<double> phase(4);
	std::fill(phase.begin(), phase.end(), 0.);
	std::vector<double> history(1);
	std::fill(history.begin(), history.end(), 0.);
	
	std::cout<<"################################################################\nOn a single element: \nwhen driving forces are set to 0:"<< std::endl;
	model.set_init(displacement, phase, history);
	
	// first we test the local stifness matrices
	// initialize the matrices and vectors
	int element = 0;
	Matrix<double> Ke_d(4,4);
	Matrix<double> Ke_d_T(4,4);
	std::vector<double>  res_d(4);
	Matrix<double> Ke_u(8,8);
	Matrix<double> Ke_u_T(8,8);
	std::vector<double> res_u(8);
	
	model.get_localStifness(element, Ke_d, res_d, Ke_u, res_u);
	model.assembly();
	
	// test if the values are correct
	// if u, d and H are all set to 0, 

	std::cout<<"Test if force vector are 0"<< std::endl;
	test.test_matching_vectors(4,tol, res_d, v_4_0);
	test.test_matching_vectors(8,tol, res_u, v_8_0);
	test.test_results();

	Ke_d.transpose(Ke_d_T);
	Ke_u.transpose(Ke_u_T);
	
	std::cout<<"Test if local matrices are symmetric"<< std::endl;
	test.test_matching_matrices(4,tol,Ke_d, Ke_d_T);
	test.test_matching_matrices(8,tol,Ke_u, Ke_u_T);
	test.test_results();
	
	std::cout<<"Test if local matrices and global matrices match"<< std::endl;
	test.test_matching_matrices(4,tol,Ke_d, *model.get_K_d());
	test.test_matching_matrices(8,tol,Ke_u, (*model.get_K_u()));
	test.test_results();


	std::cout<<"\nwhen the element is fully damaged, d=1 at all 4 nodes:"<< std::endl;
	displacement = 0;
	std::fill(phase.begin(), phase.end(), 1.);
	std::fill(history.begin(), history.end(), 0.);
	model.set_init(displacement, phase, history);
	
	model.get_localStifness(element, Ke_d, res_d, Ke_u, res_u);
	model.assembly();

	std::cout<<"Test if local matrices and global matrices match"<< std::endl;
	test.test_matching_matrices(4,tol,Ke_d, (*model.get_K_d()));
	test.test_matching_matrices(8,tol,Ke_u, (*model.get_K_u()));
	test.test_results();
	
	std::cout<<"Test if global stifness matrix is gravely degraded (elements are small)"<< std::endl;
	test.test_matching_matrices(8, tol_K, M_8_0, (*model.get_K_u()));
	test.test_results();
	
	std::cout<<"Test if local and global phase residue vector match"<< std::endl;
	test.test_matching_vectors(4,tol, res_d, model.get_Res_d());
	test.test_results();

	std::cout<<"When the Dirichlet BC are applied:"<< std::endl;
	displacement = model.get_bc_disp_value();
	std::fill(phase.begin(), phase.end(), 0.);
	std::fill(history.begin(), history.end(), 0.);
	model.set_init(displacement, phase, history);

	model.get_localStifness(element, Ke_d, res_d, Ke_u, res_u);
	model.assembly();

	std::cout<<"Test if local and global load residue vector match"<< std::endl;
	test.test_matching_vectors(8,tol, res_u, model.get_Res_u());
	test.test_results();

	
	// to implement test with 2 elements
	
	
	if (test.passed()) {std::cout<<"################################################################\n ALL TESTS PASSED\n################################################################"<< std::endl;}
	else {{std::cout<<"################################################################\n AT LEAST ONE TEST FAILED\n################################################################"<< std::endl;}}
	
	return 0;
	
	}
	
	

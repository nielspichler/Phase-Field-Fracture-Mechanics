#include "model.hpp"
#include "matrix.hpp"
#include <string>
#include <fstream>
#include <iostream> // print to console (cout)



int main(/*int argc, char *argv[]*/){
	
	double tol = 0.001;
	double tol_K = 1.;
	bool success = true;
	
	std::string file_name = "./../../examples/input_paper.inp";
	Model model(file_name);
	
	// at a given timestep we get from the previous timestep some values the phase and the history and the displacement
	
	Array<double> displacement(4,2);
	displacement = 0;
	std::vector<double> phase(4);
	std::fill(phase.begin(), phase.end(), 0.);
	std::vector<double> history(1);
	std::fill(history.begin(), history.end(), 0.);
	
	std::cout<<"On a single element, \nwhen driving forces are set to 0:"<< std::endl;
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
	std::cout<<"1st assembly"<< std::endl;
	model.assembly();
	// test if the values are correct
	// if u, d and H are all set to 0, 
	for (UInt i=0; i<res_d.size(); i++){
		if (abs(res_d[i])>tol){success = false;}
		}
	for (UInt i=0; i<res_u.size(); i++){
		if (abs(res_u[i])>tol){success = false;}
		}
	Ke_d.transpose(Ke_d_T);
	Ke_u.transpose(Ke_u_T);

	for (int i = 0; i<4;i++){
		for (int j = 0; j<4; j++){
			if(abs(Ke_d(i,j)-Ke_d_T(i,j))>tol){success = false;}
			if(abs(Ke_d(i,j)-(*model.get_K_d())(i,j))>tol){success = false;}
			}
		}
	if (success == true){std::cout<<"local residue vectors are 0"<< std::endl;}
	for (int i = 0; i<8;i++){
		for (int j = 0; j<8; j++){
			if(abs(Ke_u(i,j)-Ke_u_T(i,j))>tol){success = false;}
			if(abs(Ke_u(i,j)-(*model.get_K_u())(i,j))>tol){success = false;}
			}
		}
	if (success == true){std::cout<<"local K matrices are symmetric\nLocal and global matrices match"<< std::endl;}
	
	// fully damaged element i.e. d=1
	
	std::cout<<"When the element is fully damaged, d=1 at all 4 nodes:"<< std::endl;
	displacement = 0;
	std::fill(phase.begin(), phase.end(), 1.);
	std::fill(history.begin(), history.end(), 0.);
	model.set_init(displacement, phase, history);
	
	model.get_localStifness(element, Ke_d, res_d, Ke_u, res_u);
	model.assembly();
	for (int i = 0; i<8;i++){
		for (int j = 0; j<8; j++){
			if(abs(Ke_u(i,j))>tol_K){success = false;}
			if(abs(Ke_u(i,j)-(*model.get_K_u())(i,j))>tol){success = false;}
			}
		}
	if (success == true){std::cout<<"local K_u matrix is almost 0 everywhere\nLocal and global matrix match"<< std::endl;}
	
	for (UInt i=0; i<res_d.size(); i++){
		if (abs(res_d[i]-model.get_Res_d()[i])>tol){success = false;}
		}
	if (success == true){std::cout<<"Local and global phase residue vector match"<< std::endl;}
	
	// to implement test with 2 elements
	
	
	if (success == false) {std::cout<<"Something unexpected has happened"<< std::endl;}
	std::cout<<"SOMEHOW RAN TO THE END"<< std::endl;
	return 0;
	
	}
	
	

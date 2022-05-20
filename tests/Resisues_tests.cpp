#include "model.hpp"
#include "matrix.hpp"
#include "test_tools.hpp"

#include <string>
#include <fstream>
#include <iostream> // print to console (cout)


int main(/*int argc, char *argv[]*/){


	// initial preparations
	
	double tol = 0.0001;

	Test_tools test; // initialize a test object
	
	std::string file_name = "./../../tests/input_4_el_tests_residues.inp";
	Model model(file_name);
	
	Array<double> displacement(9,2);
	std::vector<double> Res(18);
	
	for (UInt i = 0; i<3; i++){
		
		displacement(i,0)=0.0; // u1 zero at the bottom
		displacement(i,1)=0.0; // u2 zero at the bottom
		
		displacement(i+3,0)=0.0; // u1 zero at the bottom
		displacement(i+3,1)=0.5; // u2 0.5 at the bottom
		
		displacement(i+6,0)=0.0; // u1 zero at the bottom
		displacement(i+6,1)=1.0; // u2 0.5 at the bottom
		
		}
	
	std::vector<double> phase(9);
	std::fill(phase.begin(), phase.end(), 0.0);
	std::vector<double> history(4);
	std::fill(history.begin(), history.end(), 0.0);
	model.set_init(displacement, phase, history);
	
	Matrix<double> Ke_d(4,4);
	std::vector<double>  res_d(4);
	Matrix<double> Ke_u(8,8);
	std::vector<double> res_u(8);
	
	
	model.assembly();
	
	/*
	for (UInt e = 0; e<4; e++){
		model.get_localStifness(e, Ke_d, res_d, Ke_u, res_u);
	
		std::cout<<"Res_elem: "<<e+1<<"\n"<<res_u;
	}
	Res = model.get_Res_u();
	
	std::cout<<"Res_total: \n"<<Res;
	*/
	
	std::vector<double> res_U_exp(18);
	
	std::fill(res_U_exp.begin(), res_U_exp.end(), 0.0);
	
	res_U_exp[1]= -52.5;
	res_U_exp[3]=-105.0;
	res_U_exp[5]=-52.5;
	res_U_exp[13]=52.5;
	res_U_exp[15]=105.0;
	res_U_exp[17]=-52.5;
	
	std::cout<<"Test if expected res vector"<< std::endl;
	test.test_matching_vectors(18,tol, res_U_exp, model.get_Res_u());
	test.test_results();
	
	assert(test.passed());
	
}

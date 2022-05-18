/**
 * Niels Pichler course project for class TEHPC Spring 2022
 * Phase field fracture mechanics
 * 
 * @LICENSE{
 *
 * Copyright 2022 Niels Pichler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *}
 */

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
	
	std::string file_name = "./../../tests/input_2_el_tests.inp";
	Model model(file_name);
	
	Array<double> displacement(6,2);
	displacement = 0;
	std::vector<double> phase(6);
	std::fill(phase.begin(), phase.end(), 0.2);
	std::vector<double> history(2);
	std::fill(history.begin(), history.end(), 0.3);
	
	// the 2 elements are put in random configurations
	
	for (int i=0;i<6;i++){
		phase[i] = rand();
		for (int j=0; i<2;i++){
			displacement(i,j) = 0.1 * rand();
			}
		}
	history[0] = rand(); history[1] = rand();
	
	model.set_init(displacement, phase, history);
	
	// first we test the local stifness matrices
	// initialize the matrices and vectors

	Matrix<double> Ke_d(6,6);
	std::vector<double>  res_d(6);
	Matrix<double> Ke_u(12,12);
	std::vector<double> res_u(12);
	
	model.assembly();
	Ke_u = dynamic_cast<Matrix<double>&>(*model.get_K_u());
	res_u = model.get_Res_u();
	model.apply_bc(0.5);
	
	res_u[0]=0; res_u[1]=0; res_u[6]=0; res_u[7]=0; res_u[4]=-0.1; res_u[10]=-0.1; 
	
	std::cout<<"Test if displacement residual BC works"<< std::endl;
	test.test_matching_vectors(12,tol, res_u, model.get_Res_u());
	test.test_results(); 
	
	//std::cout<<"global res_u\n"<<model.get_Res_u();
	
	for (UInt i=0; i<12; i++){
		Ke_u(0, i)=0;
		Ke_u(1, i)=0;
		Ke_u(6, i)=0;
		Ke_u(7, i)=0;
		Ke_u(4, i)=0;
		Ke_u(10, i)=0;
		}
		
		
	Ke_u(0, 0)=1;
	Ke_u(1, 1)=1;
	Ke_u(6, 6)=1;
	Ke_u(7, 7)=1;
	Ke_u(4, 4)=1;
	Ke_u(10, 10)=1;
	
	std::cout<<"Test displacement stifness matrix BC works"<< std::endl;
	test.test_matching_matrices_LT(12, tol, Ke_u, (*model.get_K_u()));
	test.test_results();


	assert(test.passed());
	
	return 0;
}


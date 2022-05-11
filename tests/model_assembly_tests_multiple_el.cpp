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
	double tol_K = 1.;
	
	std::vector<double> v_6_0(6);
	std::fill(v_6_0.begin(), v_6_0.end(), 0.);
	
	std::vector<double> v_12_0(12);
	std::fill(v_12_0.begin(), v_12_0.end(), 0.);
	
	Matrix<double> M_12_0(12,12);
	M_12_0 = 0;
	
	Test_tools test; // initialize a test object
	
	std::string file_name = "./../../tests/input_2_el_tests.inp";
	Model model(file_name);
	
	Array<double> displacement(6,2);
	displacement = 0;
	std::vector<double> phase(6);
	std::fill(phase.begin(), phase.end(), 0.2);
	std::vector<double> history(2);
	std::fill(history.begin(), history.end(), 0.3);
	
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
	
	//std::cout<<"local K_d\n"<<Ke_d;
	
	//std::cout<<"global K_d\n"<<(*model.get_K_d());
	
	//std::cout<<"local K_u\n"<<Ke_u;
	
	//std::cout<<"global K_u\n"<<(*model.get_K_u());
	
	Matrix<double> Ke_d_true(6,6);
	Ke_d_true = 0;
	Ke_d_true(0,0) = Ke_d(0,0);Ke_d_true(0,1) = Ke_d(0,1);Ke_d_true(0,4) = Ke_d(0,2);Ke_d_true(0,3) = Ke_d(0,3);
	
	Ke_d_true(1,0) = Ke_d(1,0);Ke_d_true(1,1) = Ke_d(0,0) + Ke_d(1,1);Ke_d_true(1,2) = Ke_d(0,1);Ke_d_true(1,3) = Ke_d(1,3);
		Ke_d_true(1,4) = Ke_d(1,2) + Ke_d(0,3); Ke_d_true(1,5) = Ke_d(0,2);

	Ke_d_true(2,1) = Ke_d(0,1);Ke_d_true(2,2) = Ke_d(1,1);Ke_d_true(2,4) = Ke_d(1,3); Ke_d_true(2,5) = Ke_d(1,2);
	
	Ke_d_true(3,0) = Ke_d(3,0);Ke_d_true(3,1) = Ke_d(3,1);Ke_d_true(3,4) = Ke_d(3,2);Ke_d_true(3,3) = Ke_d(3,3);
	
	Ke_d_true(4,0) = Ke_d(0,2);Ke_d_true(4,1) = Ke_d(3,0) + Ke_d(2,1);Ke_d_true(4,2) = Ke_d(3,1);Ke_d_true(4,3) = Ke_d(2,3);
		Ke_d_true(4,4) = Ke_d(3,3)+ Ke_d(2,2);Ke_d_true(4,5) = Ke_d(3,2);
	
	Ke_d_true(5,1) = Ke_d(2,0);Ke_d_true(5,2) = Ke_d(2,1);Ke_d_true(5,4) = Ke_d(2,3);Ke_d_true(5,5) = Ke_d(2,2);
	
	//std::cout<<"handmade K_d\n"<<Ke_d_true;
	
	std::cout<<"Test phase stifness matrix is properly assembled: "<< std::endl;
	test.test_matching_matrices(6, tol, Ke_d_true, (*model.get_K_d()));
	test.test_results();
	
	//std::cout<<"local K_u\n"<<Ke_u;
	
	//std::cout<<"global K_u\n"<<(*model.get_K_u());
	
	Matrix<double> Ke_u_true(12,12);
	Ke_u_true = 0;
	
	Ke_u_true(0,0) = Ke_u(0,0); 
	Ke_u_true(1,0) = Ke_u(1,0);Ke_u_true(1,1) = Ke_u(1,1);
	Ke_u_true(2,0) = Ke_u(2,0);Ke_u_true(2,1) = Ke_u(2,1);Ke_u_true(2,2) = Ke_u(2,2) + Ke_u(0,0);
	Ke_u_true(3,0) = Ke_u(3,0);Ke_u_true(3,1) = Ke_u(3,1);Ke_u_true(3,2) = Ke_u(3,2) + Ke_u(1,0);Ke_u_true(3,3) = Ke_u(3,3) + Ke_u(1,1);
	Ke_u_true(4,2) = Ke_u(2,0);Ke_u_true(4,3) = Ke_u(2,1);Ke_u_true(4,4) = Ke_u(2,2);
	Ke_u_true(5,2) = Ke_u(3,0);Ke_u_true(5,3) = Ke_u(3,1);Ke_u_true(5,4) = Ke_u(3,2);Ke_u_true(5,5) = Ke_u(3,3);
	Ke_u_true(6,0) = Ke_u(6,0);Ke_u_true(6,1) = Ke_u(6,1);Ke_u_true(6,2) = Ke_u(6,2);Ke_u_true(6,3) = Ke_u(6,3);Ke_u_true(6,6) = Ke_u(6,6);
	Ke_u_true(7,0) = Ke_u(7,0);Ke_u_true(7,1) = Ke_u(7,1);Ke_u_true(7,2) = Ke_u(7,2);Ke_u_true(7,3) = Ke_u(7,3);Ke_u_true(7,6) = Ke_u(7,6);
		Ke_u_true(7,7) = Ke_u(7,7);
		
	Ke_u_true(8,0) = Ke_u(4,0);Ke_u_true(8,1) = Ke_u(4,1);Ke_u_true(8,2) = Ke_u(4,2) + Ke_u(6,0);Ke_u_true(8,3) = Ke_u(4,3) + Ke_u(6,1);
		Ke_u_true(8,4) = Ke_u(6,2);Ke_u_true(8,5) = Ke_u(6,3);Ke_u_true(8,6) = Ke_u(4,6);Ke_u_true(8,7) = Ke_u(4,7);
			Ke_u_true(8,8) = Ke_u(4,4) + Ke_u(6,6);
	
	Ke_u_true(9,0) = Ke_u(5,0);Ke_u_true(9,1) = Ke_u(5,1);Ke_u_true(9,2) = Ke_u(7,0) + Ke_u(5,2);Ke_u_true(9,3) = Ke_u(5,3) + Ke_u(7,1);
		Ke_u_true(9,4) = Ke_u(7,2);Ke_u_true(9,5) = Ke_u(7,3);Ke_u_true(9,6) = Ke_u(5,6);Ke_u_true(9,7) = Ke_u(5,7);
			Ke_u_true(9,8) = Ke_u(5,4) + Ke_u(7,6);Ke_u_true(9,9) = Ke_u(5,5) + Ke_u(7,7);
	
	Ke_u_true(10,2) = Ke_u(4,0);Ke_u_true(10,3) = Ke_u(4,1);Ke_u_true(10,4) = Ke_u(4,2);Ke_u_true(10,5) = Ke_u(4,3);
			Ke_u_true(10,8) = Ke_u(6,4);Ke_u_true(10,9) = Ke_u(5,4);Ke_u_true(10,10) = Ke_u(4,4);

	Ke_u_true(11,2) = Ke_u(5,0);Ke_u_true(11,3) = Ke_u(5,1);Ke_u_true(11,4) = Ke_u(5,2);Ke_u_true(11,5) = Ke_u(5,3);
			Ke_u_true(11,8) = Ke_u(5,6);Ke_u_true(11,9) = Ke_u(5,7);Ke_u_true(11,10) = Ke_u(5,4);Ke_u_true(11,11) = Ke_u(5,5);
			
	//std::cout<<"handmade K_u\n"<<Ke_u_true;

	std::cout<<"Test displacement stifness matrix is properly assembled: "<< std::endl;
	test.test_matching_matrices_LT(12, tol, Ke_u_true, (*model.get_K_u()));
	test.test_results();
	
	
	return 0;
}


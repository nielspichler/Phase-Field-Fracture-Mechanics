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
	
	double tol = 0.00001;
	double tol_K = 1.;
	
	std::vector<double> v_9_0(9);
	std::fill(v_9_0.begin(), v_9_0.end(), 0.);
	
	std::vector<double> v_18_0(18);
	std::fill(v_18_0.begin(), v_18_0.end(), 0.);
	
	Matrix<double> M_18_0(18,18);
	M_18_0 = 0;
	
	Test_tools test; // initialize a test object
	
	std::string file_name = "./../../examples/input_4_el.inp";
	Model model(file_name);
	
	Array<double> displacement(9,2);
	displacement = 0;
	std::vector<double> phase(9);
	std::fill(phase.begin(), phase.end(), 0.2);
	std::vector<double> history(4);
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
	
	std::cout<<"local K_d\n"<<Ke_d;
	
	std::cout<<"global K_d\n"<<(*model.get_K_d());
	
	std::cout<<"local K_u\n"<<Ke_u;
	
	std::cout<<"global K_u\n"<<(*model.get_K_u());
	
	
	return 0;
}
	
	
	

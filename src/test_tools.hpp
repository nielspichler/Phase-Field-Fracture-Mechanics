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
#include <string>
#include <fstream>
#include <iostream> // print to console (cout)

#ifndef TEST_TOOLS_HPP
#define TEST_TOOLS_HPP

class Test_tools
{
	public:
	
	//! base constructor
	Test_tools();
	/*!
	 * @param size size of the square matrices to test
	 * @param tol tolerance accepted
	 * @param K_1 first matrix to test
	 * @param K_2 second matrix to be tested (can be any matrix inherited from BaseMatrix)
	 * tests if the 2 matrices are equal within tol
	 */
	void test_matching_matrices(int size, double tol, Matrix<double> & K_1, BaseMatrix<double> & K_2);
	/*!
	 * @param size size of the vectors to test
	 * @param tol tolerance accepted
	 * @param v_1 first vector to test
	 * @param v_2 second vector to be tested
	 * tests if the 2 vectors are equal within tol
	 */
	void test_matching_vectors(int size, double tol, std::vector<double> & v_1, std::vector<double> & v_2);
	//! will tell is the test is passed ot not 
	void test_results(){
		if (this->success == true){std::cout<<"Test passed !"<< std::endl;}
		else {std::cout<<"Test failed !"<< std::endl;}
		};
	//! will return a boolean indicating if the test is passed
	bool passed(){return this->success;};
		
	private:
		/* add your private declarations */
	//! boolean, indicated if the test is passed
	bool success;
		
};

#endif /* TEST_TOOLS_HPP */ 

/*
 * test_tools.hpp
 * 
 * Copyright 2022 student <student@tehpc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
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
	
	Test_tools();

	void test_matching_matrices(int size, double tol, Matrix<double> & K_1, BaseMatrix<double> & K_2);
	void test_matching_vectors(int size, double tol, std::vector<double> & v_1, std::vector<double> & v_2);
	
	void test_results(){
		if (this->success == true){std::cout<<"Test passed !"<< std::endl;}
		else {std::cout<<"Test failed !"<< std::endl;}
		};
	
	bool passed(){return this->success;};
		
	private:
		/* add your private declarations */
		
	bool success;
		
};

#endif /* TEST_TOOLS_HPP */ 

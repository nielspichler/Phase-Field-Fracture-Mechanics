/*
 * test_tools.cpp
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

void Test_tools::test_matching_vectors(int size, double tol, std::vector<double> & v_1, std::vector<double> & v_2)
{
	for (int i = 0; i<size;i++){
		if(abs(v_1[i]-v_2[i])>tol){this->success = false;}
		}
	if (this->success == false){std::cout<<"Test failed !"<< std::endl;}
	}




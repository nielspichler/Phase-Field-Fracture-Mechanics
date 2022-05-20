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



int main(/*int argc, char *argv[]*/)
{

	double tol = 0.001;

  std::string file_name = "./../../tests/input_tests.inp";
  Model model(file_name);
  
  bool success = true;
  std::cout<<"Tests starts"<< std::endl;
  
	if (model.get_dim() != 2){success = false;}
	else if (model.get_lc() != 0.1){success = false;}
	else if (model.get_nb_steps() != 1000){success = false;}
	else if (model.get_nb_nodes() != 4){success = false;}
	else if (model.get_nb_elements() != 1){success = false;}
	else if (model.get_nb_nodes_per_element() != 4){success = false;}
	else if (success == true){std::cout<<"General information correctly parsed"<< std::endl;}
	else {std::cout<<"Something unexpected has happened #1"<< std::endl;}

	Array<double> true_coordinates(4,2);
	true_coordinates(0,0) = 0.0; true_coordinates(0,1) = 0.0;
	true_coordinates(1,0) = 0.0; true_coordinates(1,1) = 1.0;
	true_coordinates(2,0) = 1.0; true_coordinates(2,1) = 1.0;
	true_coordinates(3,0) = 1.0; true_coordinates(3,1) = 0.0;

	for (int i = 0; i<4;i++){
		for (int j = 0; j<2; j++){
			if(abs(model.get_coordinates()(i,j)-true_coordinates(i,j))>tol){success = false;}
			}
		}

	Array<UInt> true_connectivity(1,4);
	true_connectivity(0,0) = 0; 
	true_connectivity(0,1) = 1;
	true_connectivity(0,2) = 2; 
	true_connectivity(0,3) = 3;

	for (int i = 0; i<4;i++){
			if(model.get_connectivity()(0,i)!=true_connectivity(0,i)){success = false;}
		}
	
	if (model.get_modulus()[0] != 210.0){success = false;}
	else if (model.get_poisson()[0] != 0.3){success = false;}
	else if (model.get_gc()[0] != 0.005){success = false;}
	else if (success == true){std::cout<<"Properties correctly parsed"<< std::endl;}
	else {std::cout<<"Something unexpected has happened #2"<< std::endl;}
	
	
	Array<double> true_bc_disp_value(4,2);
	true_bc_disp_value(0,0) = 0.0;true_bc_disp_value(0,1) = 0.0;
	true_bc_disp_value(1,0) = 0.0;true_bc_disp_value(1,1) = 0.0;
	true_bc_disp_value(2,0) = 0.0;true_bc_disp_value(2,1) = 0.1;
	true_bc_disp_value(3,0) = 0.0;true_bc_disp_value(3,1) = 0.1;
	
	for (int i = 0; i<4;i++){
		for (int j = 0; j<2; j++){
			if(model.get_bc_disp_value()(i,j)-true_coordinates(i,j)>tol){success = false;}
			}
		}

	if((*model.get_K_u()).nbRows()!=8){success = false;}
	else if ((*model.get_K_u()).nbCols()!=8){success = false;}
	else if ((*model.get_K_d()).nbCols()!=4){success = false;}
	else if ((*model.get_K_d()).nbRows()!=4){success = false;}
	else if (model.get_Res_u().size()!=8){success = false;}
	else if (model.get_Res_d().size()!=4){success = false;}
	else if (success == true){std::cout<<"Global matrices and vectors correctly initialized"<< std::endl;}
	else {std::cout<<"Something unexpected has happened #3"<< std::endl;}



if (success == true){std::cout<<"Model constructor 1 element: Test sucessful"<< std::endl;}


// parse second input file

  file_name = "./../../tests/input_4_el_tests.inp";
  Model model_2 (file_name);

  std::cout<<"2nd Tests starts"<< std::endl;
  
	if (model_2.get_dim() != 2){success = false;}
	else if (model_2.get_lc() != 0.1){success = false;}
	else if (model_2.get_nb_steps() != 1000){success = false;}
	else if (model_2.get_nb_nodes() != 9){success = false;}
	else if (model_2.get_nb_elements() != 4){success = false;}
	else if (model_2.get_nb_nodes_per_element() != 4){success = false;}
	else if (success == true){std::cout<<"General information correctly parsed"<< std::endl;}
	else {std::cout<<"Something unexpected has happened #1"<< std::endl;}

	true_coordinates.resize(9,2);

	true_coordinates(0,0) = 0.0; true_coordinates(0,1) = 0.0;
	true_coordinates(1,0) = 1.0; true_coordinates(1,1) = 0.0;
	true_coordinates(2,0) = 2.0; true_coordinates(2,1) = 0.0;
	
	true_coordinates(3,0) = 0.0; true_coordinates(3,1) = 1.0;
	true_coordinates(4,0) = 1.0; true_coordinates(4,1) = 1.0;
	true_coordinates(5,0) = 2.0; true_coordinates(5,1) = 1.0;
	
	true_coordinates(6,0) = 0.0; true_coordinates(6,1) = 2.0;
	true_coordinates(7,0) = 1.0; true_coordinates(7,1) = 2.0;
	true_coordinates(8,0) = 2.0; true_coordinates(8,1) = 2.0;

	for (int i = 0; i<9;i++){
		for (int j = 0; j<2; j++){
			if(abs(model_2.get_coordinates()(i,j)-true_coordinates(i,j))>tol){success = false;}
			}
		}

	if (success == true){std::cout<<"coordinates correctly parsed"<< std::endl;}

	true_connectivity.resize(4,4);
	true_connectivity(0,0) = 0; 
	true_connectivity(0,1) = 1;
	true_connectivity(0,2) = 4; 
	true_connectivity(0,3) = 3;
	
	true_connectivity(1,0) = 1; 
	true_connectivity(1,1) = 2;
	true_connectivity(1,2) = 5; 
	true_connectivity(1,3) = 4;
	
	true_connectivity(2,0) = 3; 
	true_connectivity(2,1) = 4;
	true_connectivity(2,2) = 7; 
	true_connectivity(2,3) = 6;
	
	true_connectivity(3,0) = 4; 
	true_connectivity(3,1) = 5;
	true_connectivity(3,2) = 8; 
	true_connectivity(3,3) = 7;
	
	for (int i = 0; i<4;i++){
		for (int j = 0; j<4;j++){
			if(model_2.get_connectivity()(j,i)!=true_connectivity(j,i)){success = false;}
		}
		}

	if (success == true){std::cout<<"connectivity correctly parsed"<< std::endl;}


	if (model_2.get_modulus()[0] != 210.0){success = false;}
	else if (model_2.get_poisson()[0] != 0.3){success = false;}
	else if (model_2.get_gc()[0] != 0.005){success = false;}
	else if (success == true){std::cout<<"Properties correctly parsed"<< std::endl;}
	else {std::cout<<"Something unexpected has happened #2"<< std::endl;}
	
	assert(success==true);
	
return 0;

}

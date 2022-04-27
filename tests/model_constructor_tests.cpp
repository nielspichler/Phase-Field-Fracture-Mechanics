#include "model.hpp"
#include "matrix.hpp"
#include <string>
#include <fstream>
#include <iostream> // print to console (cout)



int main(/*int argc, char *argv[]*/)
{

	double tol = 0.001;

  std::string file_name = "./../../examples/input_paper.inp";
  Model model(file_name);
  
  bool success = true;
  std::cout<<"Tests starts"<< std::endl;
  
	if (model.get_dim() != 2){success = false;}
	else if (model.get_lc() != 0.1){success = false;}
	else if (model.get_steps() != 1000){success = false;}
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

	for (int i = 0; i<2;i++){
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
	
	if (model.get_modulus()[0] != 210000.0){success = false;}
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

if (success == true){std::cout<<"Model constructor: Test sucessful"<< std::endl;}

return 0;

}

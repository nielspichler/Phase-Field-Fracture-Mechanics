#include "model.hpp"


// public methods

void Model::readInput(const std::string & fname)
{
  // character used to designate comment in input file
  char comment_char = '#';
  
  // open the file with check
  std::ifstream read_file(fname);
  assert(read_file.is_open());

  // loop over file as long as there is content
  while(!read_file.eof()) {

    // read the line
    std::string line;
    std::getline(read_file, line);

    // remove comments
    size_t found_comment = line.find_first_of(comment_char);
    if (found_comment != std::string::npos)
      line = line.substr(0,found_comment);
    if (line.empty())
      continue;

    // get first entry of line -> keyword
    std::stringstream sstr(line);
    std::string keyword;
    sstr >> keyword;

    // depending on keyword read more data
    if (keyword == "$dimensions") {
      sstr >> dim;
    }
	else if (keyword == "$lc") {
      sstr >> lc;
    }
    else if (keyword == "$steps") {
      sstr >> steps;
    }
    else if (keyword == "$nodes") {
      sstr >> nb_nodes;
    }
    else if (keyword == "$elements") {
      sstr >> nb_elements;
    }
    else if (keyword == "$elementtype") {
      int tmp;
      sstr >> tmp;
      sstr >> nb_nodes_per_element;
    }
  }
  read_file.close();
  
  // check if global properties were read
  //assert(dim >= 0);
  //assert(nb_nodes >= 0);
  //assert(nb_nodes_per_element >= 0);
  //assert(nb_elements >= 0);
  //assert(steps >= 0);
  //assert(lc >= 0.0);
  
  /* allocate arrays: 
     coordinates, 
     connectivity, modulus, cross_section, 
     bc_force, bc_disp, bc_disp_value
  */
  coordinates.resize(nb_nodes, dim);

  connectivity.resize(nb_elements, nb_nodes_per_element);
  modulus.resize(nb_elements);
  poisson.resize(nb_elements);
  gc.resize(nb_elements);
  
  // BC
  bc_disp.resize(nb_nodes, dim);
  bc_disp_value.resize(nb_nodes, dim);
  
  // initialize BC arrays with zero values
  bc_disp = 0;
  bc_disp_value=0.;
  
  // open input file again and read array values (copy and modify from week 3)
  read_file.open(fname);
  assert(read_file.is_open());

  // loop over file as long as there is content
  while(!read_file.eof()) {

    // read the line
    std::string line;
    std::getline(read_file, line);

    // remove comments
    size_t found_comment = line.find_first_of(comment_char);
    if (found_comment != std::string::npos)
      line = line.substr(0,found_comment);
    if (line.empty())
      continue;

    // get first entry of line -> keyword
    std::stringstream sstr(line);
    std::string keyword;
    sstr >> keyword;

    // depending on keyword read more data
    if (keyword == "$node") {
      int idx;
      sstr >> idx;
      sstr >> coordinates(idx-1, 0);
      sstr >> coordinates(idx-1, 1);
    }
    else if (keyword == "$element") {
      int idx;
      sstr >> idx;
      int node;
      sstr >> node;
      connectivity(idx-1, 0) = node-1; // node 1
      sstr >> node;
      connectivity(idx-1, 1) = node-1; // node 2
      sstr >> node;
      connectivity(idx-1, 2) = node-1; // node 3
      sstr >> node;
      connectivity(idx-1, 3) = node-1; // node 4
      int etype;
      sstr >> etype;
      sstr >> modulus[idx-1];
      sstr >> poisson[idx-1];
      sstr >> gc[idx-1];
    }

    else if (keyword == "$bcd") {
      int tmp;
      sstr >> tmp; // index (not used)
      int node;
      sstr >> node;
      int dir;
      sstr >> dir;
      sstr >> bc_disp_value(node-1, dir-1);
      bc_disp(node-1, dir-1) = 1; // set to ON
    }
  }
  read_file.close();
}

/*
void Model::assembly()
 {
  
  // initializing local stiffnes matrix, rotation matrix
  UInt local_size = nb_nodes_per_element*dim;
  Matrix<double> Ke(local_size, local_size);

  // initialze and fill the 2D array for mapping local indicies to global
  Matrix<double> global_indices(nb_elements, local_size);
  
  // global numbering
  for (UInt e = 0; e < nb_elements; ++e) {
    for (UInt i = 0; i < nb_nodes_per_element; ++i) {
      for (UInt j = 0; j < dim; ++j) {
	global_indices(e, 2*i+j) = j + dim * connectivity(e,i);
      }
    }
  }

  // precision value for printing on the terminal
	std::cout << "global indices" << std::endl;
	std::cout << global_indices << std::endl;


  // for loop over elements starts here
  for (UInt e = 0; e < nb_elements; ++e) {
    
    // here: call the "localStiffness" function to fill Ke
    localStiffness(e, Ke);
    // Assemble the globale stiffness matrix
    for (UInt i = 0; i < local_size; ++i) {
      for (UInt j = 0; j < local_size; ++j) {
	int gi = global_indices(e, i);
	int gj = global_indices(e, j);
	(*K)(gi, gj) += Ke(i, j);
      }      
    }
  }
  // for loop over elements end here

}
*/

void Model::apply_bc(){
	
	}

void Model::solve(){
	
	}

void Model::update(){
	
	}

void Model ::output(const std::string & odir){
	
	}

// private methods

void Model::localStiffness(int element, Matrix<double> & Ke_d, std::vector<double>  & res_d, Matrix<double> & Ke_u, std::vector<double> & res_u)
{
	int e = element;
	// resetting local stiffness and rotation matrix to zero
	Ke_d = 0.;
	Ke_u = 0.;
	// Fill local variables
	// local coordinates
	Matrix<double> loc_coordinates(nb_nodes_per_element, 2);
	// local phase
	std::vector<double> loc_d;
	loc_d.resize(nb_nodes_per_element);
	// local history
	std::vector<double> loc_H;
	loc_H.resize(nb_nodes_per_element);
	// local displacement
	std::vector<double> loc_u;
	loc_u.resize(2*nb_nodes_per_element);
	// local properties
	std::vector<double>  prop_fracture = {gc[e], lc};
	std::vector<double>  prop_elasticity = {modulus[e], poisson[e]};
	
	for (UInt i = 0;i<nb_nodes_per_element;i++)
	{
		loc_coordinates(i,0) = coordinates(connectivity(e, i),0);// x_i
		loc_coordinates(i,1) = coordinates(connectivity(e, i),1);// y_i
		
		loc_d[i] = phase[connectivity(e, i)];
		loc_H[i] = history[connectivity(e, i)];
		
		loc_u[2*i] = displacement(connectivity(e, i), 0);// u_1
		loc_u[2*i+1] = displacement(connectivity(e, i), 1);// u_2
	}
	
	// the element is created
	PhaseElement el_d(loc_coordinates, loc_d, loc_H, prop_fracture);
	DispElement el_u(loc_coordinates, loc_d, loc_u, prop_elasticity);
	// Local stiffness matrices
	el_d.GetStiffnessAndRes(Ke_d, res_d);
	el_u.GetStiffnessAndRes(Ke_u, res_u);
}


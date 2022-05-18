#include "model.hpp"


// public methods

void Model::readInput(const std::string & fname)
{

  std::cout<<"Parsing input file \n";
  // character used to designate comment in input file
  char comment_char = '#';
  
  // open the file with check
  std::ifstream read_file(fname);
  
    if (!read_file.is_open()){
	  std::cout<<"could not open the input file\n";
	  assert(read_file.is_open());
	  }

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
      sstr >> nb_steps;
    }
	else if (keyword == "$damage") {
      sstr >> damage;
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
  
  /* allocate arradisplacement = 0;ys: 
     coordinates, 
     connectivity, modulus, cross_section, 
     bc_force, bc_disp, bc_disp_value
  */
  coordinates.resize(nb_nodes, dim);

  connectivity.resize(nb_elements, nb_nodes_per_element);
  modulus.resize(nb_elements);
  poisson.resize(nb_elements);
  gc.resize(nb_elements);
  
  phase.resize(nb_nodes);
  std::fill(phase.begin(), phase.end(), 0.);
  
  // BC
  bc_disp.resize(nb_nodes, dim);coordinates.resize(nb_nodes, dim);
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
  
  // initialize matrices size
  
  K_u = std::shared_ptr<BaseMatrix<double> >(new Matrix<double>(nb_nodes * dim, nb_nodes * dim));
  K_d = std::shared_ptr<BaseMatrix<double> >(new Matrix<double>(nb_nodes, nb_nodes));

  Res_u.resize(nb_nodes, dim);
  Res_u = 0.;
  Res_d.resize(nb_nodes);
  std::fill(Res_d.begin(), Res_d.end(), 0.);
  
  dphase.resize(nb_nodes);
  std::fill(dphase.begin(), dphase.end(), 0.);
  
  history.resize(nb_nodes);
  std::fill(history.begin(), history.end(), 0.);
  displacement.resize(nb_nodes, dim);
  displacement = 0.;
  ddisplacement.resize(nb_nodes, dim);
  ddisplacement = 0.;
  
}

void Model::assembly()
 {
  
  // reset everything to 0
  (*K_u) = 0.0;
  (*K_d) = 0.0;
  
  Res_u = 0.;
  std::fill(Res_d.begin(), Res_d.end(), 0.);
  
  // initializing local stiffnes matrix, residue vect
  UInt local_size_u = nb_nodes_per_element*dim;
  Matrix<double> Ke_u(local_size_u, local_size_u);
  std::vector<double>  res_u(local_size_u);
  
  UInt local_size_d = nb_nodes_per_element;
  Matrix<double> Ke_d(local_size_d, local_size_d);
  std::vector<double>  res_d(local_size_d);

  // initialze and fill the 2D array for mapping local indicies to global
  Matrix<double> global_indices_u(nb_elements, local_size_u);
  Matrix<double> global_indices_d(nb_elements, local_size_d);
  
  // global numbering
  for (UInt e = 0; e < nb_elements; ++e) {
    for (UInt i = 0; i < nb_nodes_per_element; ++i) {
      for (UInt j = 0; j < dim; ++j) {
          global_indices_u(e, 2*i+j) = j + dim * connectivity(e,i);
      }
      global_indices_d(e, i) = connectivity(e,i); // ???
    }
  }
  
  #ifdef TEHPC_VERBOSE
  // precision value for printing on the terminal
	std::cout << "global indices_u" << std::endl;
	std::cout << global_indices_u << std::endl;
	std::cout << "global indices_d" << std::endl;
	std::cout << global_indices_d << std::endl;
  #endif /* THEPC_VERBOSE */
  
  // for loop over elements starts here
  for (UInt e = 0; e < nb_elements; ++e) {
    
    // here: call the "localStiffness" function to fill Ke_s and res_s
    localStiffness(e, Ke_d, res_d, Ke_u, res_u);
    
    // Assemble the global stiffness matrix
    for (UInt i = 0; i < local_size_u; ++i) {
      int gi = global_indices_u(e, i);
      Res_u.getStorage()[gi] += res_u[i];
      for (UInt j = 0; j < local_size_u; ++j) {
			int gj = global_indices_u(e, j);
			(*K_u)(gi, gj) += Ke_u(i, j);
      }
    }
    for (UInt i = 0; i < local_size_d; ++i) {
      int gi = global_indices_d(e, i);
      Res_d[gi] += res_d[i];
      for (UInt j = 0; j < local_size_d; ++j) {
			int gj = global_indices_d(e, j);
			(*K_d)(gi, gj) += Ke_d(i, j);
      }
    }
  }
  // for loop over elements end here
}

void Model::apply_bc(double fraction)
{
  // fraction if the percentage of load applied (0 means no displacement, 1 means the full didirchlet BC is applied)
  // impose Dirichlet BC: adapt K, such that disp can be put in force
  // see TUM FE poly page 82 and 83
  for (UInt n=0; n<nb_nodes; ++n) {
    for (UInt d=0; d<dim; ++d) {
		  if (bc_disp(n,d)) { // was set to 1 if BC is applied, 0 else in the constructor
			Res_u.getStorage()[n*dim + d] = -1.*fraction * bc_disp_value(n,d); // override force vector
			for (UInt m=0; m<nb_nodes*dim; ++m) {
			  (*(K_u))(n*dim+d,m) = 0.; // sets line to 0
			}
			(*(K_u))(n*this->dim+d,n*this->dim+d) = 1.; // diagonal to 1
		}
    }
  }
}

void Model::registerSolver(std::shared_ptr<NLsolver> solver_set) 
{
    solver = solver_set;
  }

void Model::solve()
{
	#ifdef TEHPC_VERBOSE
	std::cout << "Displacement matrix: " << std::endl;
    std::cout << (*(K_u)) << std::endl;
    std::cout << "Res_u matrix: " << std::endl;
    std::cout << Res_u.getStorage() << std::endl;
    #endif /* THEPC_VERBOSE */
    // call the solver (and the necessary input of the solver)
    solver->solve(K_u, Res_u.getStorage() * (-1.), ddisplacement.getStorage());
    displacement.getStorage() = displacement.getStorage() + ddisplacement.getStorage();
    // print solution to terminal (next time to file)
    if (damage){
    #ifdef TEHPC_VERBOSE
    std::cout << "solution:" << std::endl;
    std::cout << displacement << std::endl;
	std::cout << "Phase matrix: " << std::endl;
    std::cout << (*(K_d)) << std::endl;
    std::cout << Res_d << std::endl;
    #endif /* THEPC_VERBOSE */
    /* Your solution goes here */
    // call the solver (and the necessary input of the solver)
    solver->solve(K_d, Res_d * (-1.), dphase);
    phase = phase + dphase;
    // print solution to terminal (next time to file)
    #ifdef TEHPC_VERBOSE
    std::cout << "solution:" << std::endl;
    std::cout << phase << std::endl;
    #endif /* THEPC_VERBOSE */
    }
	}

void Model::output_nodal(const std::string & odir, const std::vector<double> & nodal_value, const std::string & field_name)
{
	
	std::ofstream output_file("./" + odir + "/output_" + Name + field_name +".dat", std::ios::app);
	assert(output_file.is_open());
	
	output_file.precision(10);
	
	if (step == 0){
		//output_file << field_name <<"_results_node_number:";
		for(UInt i = 0; i<nb_nodes; i++){
			if (i==0){output_file <<"Node_"<< i;}
			else{output_file <<" Node_"<< i;} // writes the x coordinate
			}
		//output_file << "\nX_coord:";
		output_file << "\n";
		for(UInt i = 0; i<nb_nodes; i++){
			if (i==0){output_file << coordinates(i,0);}
			else{output_file <<" "<< coordinates(i,0);} // writes the x coordinate
			}
		//output_file << "\nY_coord:";
		output_file << "\n";
		for(UInt i = 0; i<nb_nodes; i++){
			if (i==0){output_file << coordinates(i,1);}
			else{output_file <<" "<< coordinates(i,1);}  // writes the y coordinate
			}
		}
	//output_file << "\nStep_"<<step<<":";
	output_file << "\n";
	for(UInt i = 0; i<nb_nodes; i++){
		if (i==0){output_file  << nodal_value[i];} // writes the y coordinate
		else{output_file <<" "<< nodal_value[i];}
		}
	assert(output_file.good());
	output_file.close();
	
	}

void Model::output_elemental(const std::string & odir, const std::vector<double> & elemental_value, const std::string & field_name)
{
	
	std::ofstream output_file("./" + odir + "/output_" + Name + field_name +".dat", std::ios::app);
	assert(output_file.is_open());
	
	output_file.precision(10);

	
	if (step == 0){
		//output_file << field_name <<"_results_element_number:";
		
		for(UInt i = 0; i<nb_elements; i++){
			if (i==0){output_file <<"element_"<< i;}
			else{output_file <<" element_"<< i;} // writes the x coordinate
			}
		
		}
	//output_file << "\nStep_"<<step<<":";
	output_file << "\n";
	for(UInt i = 0; i<nb_elements; i++){
		if (i==0){output_file  << elemental_value[i];}
		else{output_file  << " "<< elemental_value[i];} // writes the y coordinate
		}
	assert(output_file.good());
	output_file.close();
	
	}

void Model::iterate(const std::string & sim_name, std::string & odir)
{
	Name = sim_name;
	
	std::shared_ptr<LU_solver> solver;
	solver = std::make_shared<LU_solver>(500, 1e-6);
	registerSolver(solver);
	
	std::cout<<"start of iterations\n";
	for (UInt step = 0; step<nb_steps; step++){
		
		this->step = step;
		std::cout<< "\r"<<"step: "<<step+1<< std::flush;
		assembly();
		
		output_nodal(odir, Res_u(0), "F1");
		output_nodal(odir, Res_u(1), "F2");
		
		apply_bc((1.0)/nb_steps); // thanks to the +1.0 the fraction of UInts is a double
		
		solve();
		
		output_nodal(odir, displacement(0), "u1");
		output_nodal(odir, displacement(1), "u2");
		output_nodal(odir, phase, "Phase");
		output_elemental(odir, history, "H");
		
		}
	
	std::cout<<"\nSIMULATION FINISHED ! :) \n";
	
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
		
		loc_u[2*i] = displacement(connectivity(e, i), 0);// u_1
		loc_u[2*i+1] = displacement(connectivity(e, i), 1);// u_2
	}

	double loc_H = history[e];
	
	// the element is created
	DispElement el_u(loc_coordinates, loc_d, loc_u, loc_H, prop_elasticity); // Disp element is created
	el_u.GetStiffnessAndRes(Ke_u, res_u); // Sets the displacement matrix and residue also updates history variable if needed
	
	loc_H = el_u.get_H(); // the variable is updated
	history[e] = loc_H; // the variable is stored
	
	PhaseElement el_d(loc_coordinates, loc_d, loc_H, prop_fracture); // the phase matrix is computed using the new history
	el_d.GetStiffnessAndRes(Ke_d, res_d);

}

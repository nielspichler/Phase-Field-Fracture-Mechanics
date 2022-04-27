#ifndef __MODEL__HH__
#define __MODEL__HH__

#include <string>
#include <fstream>
#include <sstream>

#include "common.hpp"
#include "array.hpp"
#include "matrix.hpp"


#include "phaseelement.hpp"
#include "dispelement.hpp"
#include "newton_raphson_solver.hpp"


using UInt = unsigned int;

class Model {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  Model() = default;
  
  Model(const std::string & fname) {
    this->readInput(fname);
  };
  
  virtual ~Model() = default;


  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:

  // reads input file and assigns values to members
  void readInput(const std::string & fname);

  // assembles global stiffness matrix K
  void assembly();
  
  // reduces the stifness matrices
  void apply_bc(); 

  // solves the equation
  void solve(); 
  
  // updates the variables
  void update(); 
  
  // stores the phase field variable in an output directory
  void output(const std::string & odir); 


private:
  void localStiffness(int element, Matrix<double> & Ke_d, std::vector<double>  & res_d, Matrix<double> & Ke_u, std::vector<double> & res_u);


  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:

  //Matrix<double> * getK() { return this->K; };
  
  // these accessors are needed to test the parsing of the file
  UInt get_dim(){return this->dim;};
  double get_lc(){return this->lc;};
  UInt get_steps(){return this->steps;};
  UInt get_nb_nodes(){return this->nb_nodes;};
  Array<double> get_coordinates(){return this->coordinates;};
  UInt get_nb_elements(){return this->nb_elements;};
  UInt get_nb_nodes_per_element(){return this->nb_nodes_per_element;};
  Array<UInt> get_connectivity(){return this->connectivity;};
  std::vector<double> get_modulus(){return this->modulus;};
  std::vector<double> get_poisson(){return this->poisson;};
  std::vector<double> get_gc(){return this->gc;};
  Array<UInt> get_bc_disp(){return this->bc_disp;};
  Array<double> get_bc_disp_value(){return this->bc_disp_value;};
  
  // this is needed to test the local stifness construction
	void get_localStifness(int element, Matrix<double> & Ke_d, std::vector<double>  & res_d, Matrix<double> & Ke_u, std::vector<double> & res_u){
	localStiffness(element, Ke_d, res_d, Ke_u, res_u);
	};
	// to set all required variables to run local stifness in the test
	void set_init(Array<double> d, std::vector<double> p, std::vector<double> h){
		displacement.resize(d.nbRows(), d.nbCols());
		displacement = d;
		phase.resize(p.size());
		phase = p;
		history.resize(h.size());
		history = h;
	};


  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
private:

  // general information
  UInt dim;
  double lc;
  UInt steps;

  // nodal information
  UInt nb_nodes;
  Array<double> coordinates;
  Array<double> displacement;		//u
  std::vector<double> phase;		//d
  std::vector<double> history;		//H

  // elemental information
  UInt nb_elements;
  UInt nb_nodes_per_element;
  Array<UInt> connectivity;
  std::vector<double> modulus;
  std::vector<double> poisson;
  std::vector<double> gc;

  // boundary conditions (nodal information)
  Array<UInt> bc_disp;
  Array<double> bc_disp_value;

  // global stiffness matrix
  std::shared_ptr<BaseMatrix<double> > K;

  // pointer to solver used
  std::shared_ptr<NRsolver> solver;
};

#endif

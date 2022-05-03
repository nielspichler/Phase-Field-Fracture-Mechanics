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
  void apply_bc(double fraction); 

  // registers a solver to the model
  void registerSolver(std::shared_ptr<NRsolver> solver);

  // solves the equation
  void solve(); 
  
  // stores the phase field variable in an output directory
  void output(const std::string & odir, const std::vector<double> & nodal_value, const std::string & field_name); 

  void iterate(const std::string & sim_name, std::string & odir);

private:
  void localStiffness(int element, Matrix<double> & Ke_d, std::vector<double>  & res_d, Matrix<double> & Ke_u, std::vector<double> & res_u);


  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:

  std::shared_ptr<BaseMatrix<double> > get_K_u() { return this->K_u; };
  std::shared_ptr<BaseMatrix<double> > get_K_d() { return this->K_d; };
  std::vector<double> get_Res_u() {return this->Res_u.getStorage();};
  std::vector<double> get_Res_d() {return this->Res_d;};
  std::vector<double> & get_Phase() {return this->phase;};
  
  // these accessors are needed to test the parsing of the input file
  UInt get_dim(){return this->dim;};
  double get_lc(){return this->lc;};
  UInt get_nb_steps(){return this->nb_steps;};
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
  UInt nb_steps;
  UInt step = 0;
  std::string Name = "default";

  // nodal information
  UInt nb_nodes;
  Array<double> coordinates;
  Array<double> displacement;		//u
  std::vector<double> phase;		//d


  // elemental information
  UInt nb_elements;
  UInt nb_nodes_per_element;
  Array<UInt> connectivity;
  std::vector<double> modulus;
  std::vector<double> poisson;
  std::vector<double> gc;
  std::vector<double> history;		//H

  // boundary conditions (nodal information)
  Array<UInt> bc_disp;
  Array<double> bc_disp_value;

  // global stiffness matrix
  std::shared_ptr<BaseMatrix<double> > K_u;
  std::shared_ptr<BaseMatrix<double> > K_d;
  
  // global residue vectors 
  Array<double> Res_u;
  std::vector<double> Res_d;

  // pointer to solver used
  std::shared_ptr<NRsolver> solver;
};

#endif

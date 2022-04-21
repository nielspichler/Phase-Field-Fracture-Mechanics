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
  
  ~Model();


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
  void localStiffness(int element, Matrix<double> & Ke);


  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:

  Matrix<double> * getK() { return this->K; };


  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
private:

  // general information
  UInt dim;
  double lc;

  // nodal information
  UInt nb_nodes;
  Array<double> coordinates;
  Array<double> displacement;	//u
  Array<double> phase;			//d
  Array<double> history;		//H
  Array<double> force;

  // elemental information
  UInt nb_elements;
  UInt nb_nodes_per_element;
  Array<UInt> connectivity;
  std::vector<double> modulus;
  std::vector<double> poisson;
  std::vector<double> gc;
  std::vector<double> cross_section;

  // boundary conditions (nodal information)
  Array<double> bc_force;
  Array<UInt> bc_disp;
  Array<double> bc_disp_value;

  // global stiffness matrix
  std::shared_ptr<BaseMatrix<double> > K;

  // pointer to solver used
  std::shared_ptr<NLsolver> solver;
};

#endif

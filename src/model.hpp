#ifndef __MODEL__HH__
#define __MODEL__HH__

#include <string>
#include <fstream>
#include <sstream>

#include "arithmetic_operations.h"
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


private:
  void localStiffness(int element, Matrix & Ke);

  void fillRotationMatrix(Matrix & R, double sine, double cosine);


  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:

  Matrix * getK() { return this->K; };


  /* ------------------------------------------------------------------------ */
  /* Class Members                                                            */
  /* ------------------------------------------------------------------------ */
private:

  // general information
  int dim;

  // nodal information
  UInt nb_nodes;
  Matrix coordinates;

  // elemental information
  UInt nb_elements;
  UInt nb_nodes_per_element;
  Matrix connectivity;
  std::vector<double> modulus;
  std::vector<double> cross_section;

  // boundary conditions (nodal information)
  Matrix bc_force;
  int ** bc_disp = NULL;
  Matrix bc_disp_value;

  // global stiffness matrix
  Matrix * K = NULL;
};

#endif

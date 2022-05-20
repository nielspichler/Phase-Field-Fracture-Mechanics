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
#include "lu_solver.hpp"
#include "newton_raphson_solver.hpp"

using UInt = unsigned int;

class Model {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  Model() = default;
  
  /*!
   * @param fname name of the input file
   * constructor for the model class will parse the input file and set all parameters
   */
  Model(const std::string & fname) {
    this->readInput(fname);
  };
  
  virtual ~Model() = default;


  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:

  //! reads input file and assigns values to members
  void readInput(const std::string & fname);

  //! assembles global stiffness matrix K_u and K_d
  void assembly();
  
  /// reduces the stifness matrices
  void apply_bc(double fraction); 

  /*! @param solver shared pointer to an object of class NLsolver 
   * register a solver
   */
  void registerSolver(std::shared_ptr<NLsolver> solver);

  //! solves the equation
  void solve_step(); 
  
  //! solves the equation
  void solve(); 
  
  /*!
   * @param odir output directory name
   * @param nodal_value A vector containing the nodal values to output
   * @param field_name the name of the variable that is being outputted
   *  stores a nodal field variable in an output directory
   */
  void output_nodal(const std::string & odir, const std::vector<double> & nodal_value, const std::string & field_name); 
  /*!
   * @param odir output directory name
   * @param elemental_value A vector containing the elemental values to output
   * @param field_name the name of the variable that is being outputted
   *  stores an elemental field variable in an output directory
   */
  void output_elemental(const std::string & odir, const std::vector<double> & elemental_value, const std::string & field_name);
  /*!
   * @param sim_name simulation name
   * @param odir output directory to dump the results
   */
  
  void iterate(const std::string & sim_name, std::string & odir);

private:

  /*!
   * @param element element number
   * @param Ke_d local phase stifness matrix
   * @param res_d local phase residue vector
   * @param Ke_u local displacement stifness matrix
   * @param res_u local displacement residue vector
   * given an element number this method will set the local stifness matrices and residue vectors
   */
  void localStiffness(int element, Matrix<double> & Ke_d, std::vector<double>  & res_d, Matrix<double> & Ke_u, std::vector<double> & res_u);


  /* ------------------------------------------------------------------------ */
  /* Accessors                                                                */
  /* ------------------------------------------------------------------------ */
public:
  //! returns the global displacement stifness matrix (for tests)
  std::shared_ptr<BaseMatrix<double> > get_K_u() { return this->K_u; };
  //! returns the global phase stifness matrix (for tests)
  std::shared_ptr<BaseMatrix<double> > get_K_d() { return this->K_d; };
  //! returns the global displacement residue vector (for tests)
  std::vector<double> & get_Res_u() {return this->Res_u.getStorage();};
  //! returns the global phase residue vector (for tests)
  std::vector<double> & get_Res_d() {return this->Res_d;};
  //! returns the phase vector (for tests)
  std::vector<double> & get_Phase() {return this->phase;};
  
  // these accessors are needed to test the parsing of the input file
  //! returns the dimension (for tests)
  UInt get_dim(){return this->dim;};
  //! returns lc (for tests)
  double get_lc(){return this->lc;};
  //! returns the number of steps (for tests)
  UInt get_nb_steps(){return this->nb_steps;};
  //! returns the number of nodes (for tests)
  UInt get_nb_nodes(){return this->nb_nodes;};
  //! returns the coordinates (for tests)
  Array<double> get_coordinates(){return this->coordinates;};
  //! returns the total number of elements (for tests)
  UInt get_nb_elements(){return this->nb_elements;};
  //! returns the number of nodes per elements (for tests)
  UInt get_nb_nodes_per_element(){return this->nb_nodes_per_element;};
  //! returns the connectivity (for tests)
  Array<UInt> get_connectivity(){return this->connectivity;};
  //! returns the Young modulus of all elements (for tests)
  std::vector<double> get_modulus(){return this->modulus;};  
  //! returns the poisson ratio of all elements (for tests)
  std::vector<double> get_poisson(){return this->poisson;};
  //! returns the critical ERR of all elements (for tests)
  std::vector<double> get_gc(){return this->gc;};
  //! returns the applied displacements (for tests)
  Array<UInt> get_bc_disp(){return this->bc_disp;};
  //! returns the boolean matrix setting wether or not a BC must be enforced (for tests)
  Array<double> get_bc_disp_value(){return this->bc_disp_value;};
  //! sets the local stifness matrices and local residue vectors
	void get_localStifness(int element, Matrix<double> & Ke_d, std::vector<double>  & res_d, Matrix<double> & Ke_u, std::vector<double> & res_u){
	localStiffness(element, Ke_d, res_d, Ke_u, res_u);
	};
	/*! 
	 * @param d displacements
	 * @param p phase
	 * @param h history field
	 * a utility method to set the model in a certain state to run tests 
	 */
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
  //! dimention of the model
  UInt dim;
  //! length scale parameter
  double lc;
  //! number of steps
  UInt nb_steps;
  //! step number
  UInt step = 0;
  //! simulation name
  std::string Name = "default";
  //! sets if damage is active
  UInt damage = 1;

  // nodal information
  //! number of nodes
  UInt nb_nodes;
  //! array of coordinates, each row contains the coordinnates of a node
  Array<double> coordinates;
  //! array of displacement, each row contains the displecement of a node in cartesian coorditanes
  Array<double> displacement;		//u
  //! array of incremental displacement, each row contains incrmental the displecement of a node in cartesian coorditanes
  Array<double> ddisplacement;		//u
  //! vector of phase, each entry is the phase of a node
  std::vector<double> phase;		//d
  //! vector of incremental phase, each entry is the increment in phase of a node
  std::vector<double> dphase;

  // elemental information
  //! total number of elements
  UInt nb_elements;
  //! number of nodes per element
  UInt nb_nodes_per_element;
  //! connectivity array, each row contains the list of nodes of an element
  Array<UInt> connectivity;
  //! contains the Young's modulus of the elements
  std::vector<double> modulus;
  //! contains the Poisson ratio of the elements
  std::vector<double> poisson;
  //! contains the critical ERR of the elements
  std::vector<double> gc;
  //! contains the history of the elements
  std::vector<double> history;		//H

  // boundary conditions (nodal information)
  //! 1 if BC is to be enforced, 0 if DOF is free
  Array<UInt> bc_disp;
  //! Neumann BC in cartesian coorditanes
  Array<double> bc_disp_value;

  // global stiffness matrix
  //! global displacement stiffness matrix
  std::shared_ptr<BaseMatrix<double> > K_u;
  //! global phase stiffness matrix
  std::shared_ptr<BaseMatrix<double> > K_d;
  
  // global residue vectors 
  //! global displacement residue vector (nodal forces)
  Array<double> Res_u;
  //! global phase residue vector
  std::vector<double> Res_d;

  //! pointer to solver used
  std::shared_ptr<NLsolver> solver;
};

#endif

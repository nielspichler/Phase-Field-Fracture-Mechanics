

#ifndef DISPELEMENT_HPP
#define DISPELEMENT_HPP

#include "element.hpp"

class DispElement: public Element
{
	public:
		DispElement();
		/*!
		 * @param loc_coordinates coordinates of the nodes, each row contains the x and y coordinate of each node
		 * @param loc_d, nodal value of the phase
		 * @param loc_u, nodal displacements in a single vector, the first 2 are the vertical and horizontal displacement of the first node and so on
		 * @param loc_H, elemental valur of the history variable H
		 * @param prop a vector containing the Young modulus and the poisson ration, in that order
		 * Constructor for the displacement element
		 */
		DispElement(Matrix<double> & loc_coordinates, std::vector<double> & loc_d, std::vector<double> & loc_u, double & loc_H, std::vector<double> & prop);
		
		/*!
		 * @param Ke local stifness matrix
		 * @param res local residue vector
		 * Inherited from the element class, will set both arguments for an element
		 */
		void GetStiffnessAndRes(Matrix<double> & Ke, std::vector<double> & res);
		double get_H(){
			return H;
			}
		
	private:
		//! Strain matrix, 
		Matrix<double> B;
		//! Transposed strain matrix, 
		Matrix<double> B_T;
		//! Plane strain elastic stifness matrix (Hook's law)
		Matrix<double> C;
		//! strain at a integration point
		std::vector<double> eps;
		//! stress at a integration point
		std::vector<double> sig;
		//! history variable of the element
		double H;
		//! elastic strain energy of the element
		double psi_0;
		//! numerical stabilizaiton factor
		double k;
		
};

#endif /* DISPELEMENT_HPP */ 

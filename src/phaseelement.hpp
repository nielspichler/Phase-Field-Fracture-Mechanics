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

#ifndef PHASEELEMENT_HPP
#define PHASEELEMENT_HPP

#include "element.hpp"

class PhaseElement: public Element
{
	public:
		PhaseElement();
		/*!
		 * @param loc_coordinates coordinates of the nodes, each row contains the x and y coordinate of each node
		 * @param d  nodal values of the phase
		 * @param H  elemental value of the history variable H
		 * @param prop a vector containing the critical ERR and Lc
		 * Constructor for the displacement element the local node numbering is counterclockwise
		 */
		PhaseElement(Matrix<double> & loc_coordinates, std::vector<double> & d, double & H, std::vector<double> & prop);
		
		// Methods
				/*!
		 * @param Ke local stifness matrix
		 * @param res local residue vector
		 * Inherited from the element class, will set both arguments for an element
		 */
		void GetStiffnessAndRes(Matrix<double> & Ke, std::vector<double> & res);
		
		
	private:
		// Members
		//! contains the gradient of the phase
		std::vector<double> gradd;
		
};

#endif /* PHASEELEMENT_HPP */ 

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


#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "matrix.hpp"
#include <cassert>
#include <math.h>

class Element
{
	public:
		Element();
		
		// Methods
		/*!
		 * @param Ke local stifness matrix
		 * @param res local residue vector
		 * Set both arguments for an element
		 */
		virtual void GetStiffnessAndRes(Matrix<double> & Ke, std::vector<double> & res)=0;
		
	protected:
		// Members
		//! coordinates of the nodes, each row contains the x and y coordinate of each node
		Matrix<double> coordinates;
		//! a vector containing material properties for the element
		std::vector<double> prop;			// Vector containing the material properties (E, nu...) or (lc, g...)
		//! contains the integration points coordinates
		Matrix<double> intpt;						// 4 by 2 contains the integration points coordinates
		//! nodal value of the phase
		std::vector<double> nodal_d; 		// 4 contains nodal values of d
		//! odal displacements in a single vector, the first 2 are the vertical and horizontal displacement of the first node and so on
		std::vector<double> nodal_u; 		// 8 contains nodal value of u (u1, u2, u1, u2...)
		//! dimension of the element
		int dim;
		
		//! Matrix of shape functions
		Matrix<double> N; // 1x4
		//! Transposed matrix of shape functions
		Matrix<double> N_T; // 4x1
		//! Matrix of shape functions derivative (isoparametric)
		Matrix<double> dNdxi; // 2x4
		//! vector containing the local coordinates of the integration point
		std::vector<double> xi; // 2x1
		//! Jacobian matrix
		Matrix<double> J;// 2X2
		//! inverse Jacobian matrix
		Matrix<double> invJ;// 2X2
		//! Matrix of shape functions derivative (real space)
		Matrix<double> dNdx;// 2x4
		//! Transposed matrix of shape functions derivative (real space)
		Matrix<double> dNdx_T;// 4x2
		//! determinant of the Jacobian
		double det;
		//! phase at integration point
		double d; 
		//! weight in gauss integration
		double w;
		//! elemental H
		double H; 
		// Methods
		/*!
		 * @param dNdxi Matrix of shape functions derivative (isoparametric)
		 * @param N Matrix of shape functions
		 * @param xi vector containing the local coordinates of the integration point
		 * this method will evaluate the 4 shape functions and their derivative at the integration point xi 
		 */
		void ShapeFun_4lin(Matrix<double> & dNdxi, Matrix<double> & N, std::vector<double> & xi);
		
};

#endif /* ELEMENT_HPP */ 









/*
 * element.hpp
 * 
 * Copyright 2022 student <student@tehpc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
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
		
		virtual void GetStiffnessAndRes(Matrix & Ke, std::vector<double> & res)=0;
		
	protected:
		// Members
		Matrix coordinates;					// 4 by 2 containing the x and y coordinate of each node
		std::vector<double> prop;			// Vector containing the material properties (E, nu...) or (lc, g...)
		Matrix intpt;						// 4 by 2 contains the integration points coordinates
		std::vector<double> nodal_d; 		// 4 contains nodal values of d
		std::vector<double> nodal_H; 		// 4 contains nodal value of H
		std::vector<double> nodal_u; 		// 8 contains nodal value of u (u1, u2, u1, u2...)
		int dim;
		
		Matrix N; // 1x4
		Matrix N_T; // 4x1
		Matrix dNdxi; // 2x4
		std::vector<double> xi; // 2x1
		Matrix J;// 2X2
		Matrix invJ;// 2X2
		Matrix dNdx;// 2x4
		Matrix dNdx_T;// 4x2
		double det;
		double d;
		double w; // weight in gauss integration
		double H;
		// Methods
		void ShapeFun_4lin(Matrix & dNdxi, Matrix & N, std::vector<double> & xi);
		
};

#endif /* ELEMENT_HPP */ 









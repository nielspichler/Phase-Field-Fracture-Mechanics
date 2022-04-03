/*
 * element.cpp
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


#include "element.hpp"


Element::Element()
{
	
}


void Element::ShapeFun_4lin(Matrix & dNdxi, Matrix & N, std::vector<double> & xi)
{
	// Evaluating the shape functions at the integration points
	N(0, 0) = 0.25 * (1-xi[0]) * (1-xi[1]);
	N(0, 1) = 0.25 * (1+xi[0]) * (1-xi[1]);
	N(0, 2) = 0.25 * (1+xi[0]) * (1+xi[1]);
	N(0, 3) = 0.25 * (1-xi[0]) * (1+xi[1]);
	
	// Evaluating the shape functions derivatives et the integration points
	
	dNdxi(0,0) = -0.25 * (1-xi[1]);
	dNdxi(0,1) = 0.25 * (1-xi[1]);
	dNdxi(0,2) = 0.25 * (1+xi[1]);
	dNdxi(0,3) = -0.25 * (1+xi[1]);
	dNdxi(1,0) = -0.25 * (1-xi[0]);
	dNdxi(1,1) = -0.25 * (1+xi[0]);
	dNdxi(1,2) = 0.25 * (1+xi[0]);
	dNdxi(1,3) = 0.25 * (1-xi[0]);
	
	}






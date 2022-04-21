/*
 * phaseelement.cpp
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


#include "phaseelement.hpp"


PhaseElement::PhaseElement(Matrix<double> & loc_coordinates, std::vector<double> & loc_d, std::vector<double> & loc_H, std::vector<double> & prop)
{
	coordinates = loc_coordinates;
	nodal_d = loc_d;
	nodal_H = loc_H;
	
	int dim = 2;
	
	if (coordinates.nbRows()==4) // 4 node elements
	{
		Matrix<double> intpt(4,2);
		intpt(0,0) = -1/pow(3,0.5);
		intpt(0,1) = -1/pow(3,0.5);
		intpt(1,0) = 1/pow(3,0.5);
		intpt(1,1) = -1/pow(3,0.5);
		intpt(2,0) = 1/pow(3,0.5);
		intpt(2,1) = 1/pow(3,0.5);
		intpt(3,0) = -1/pow(3,0.5);
		intpt(3,1) = 1/pow(3,0.5);
	}
	N.resize(1,coordinates.nbRows()); // 1x4
	N_T.resize(coordinates.nbRows(), 1); // 4x1
	dNdxi.resize(coordinates.nbRows(), dim); // 2x4
	xi.resize(coordinates.nbRows());
	J.resize(dim, dim);// 2X2
	//invJ.resize(dim, dim);// 2X2
	dNdx.resize(coordinates.nbRows(), dim);// 2x4
	dNdx_T.resize(dim, coordinates.nbRows());// 4x2
	det=0.;
	d=0.;
	H=0.;
	w = 1.; // weight in gauss integration

}

void PhaseElement::GetStiffnessAndRes(Matrix<double> & Ke, std::vector<double> & res)
{
	Ke = 0.;
	std::fill(res.begin(), res.end(), 0.);
	
	for (int i=0; i<intpt.nbRows(); i++) // loop over the integration points
	{
		xi[0] = intpt(i,0);
		xi[1] = intpt(i,1);
		ShapeFun_4lin(dNdxi, N, xi); // evaluates the shape functions at the integration point
		J = dNdxi * coordinates; // 2x2 = 2x4*4x2
		det = J.determinant(); // could be faster is computed "by hand"
		assert(det!=0);
		J.inverse(invJ); // 2x2
		dNdx = invJ * dNdxi; // 2x4 = 2x2*2x4 also called B matrix
		
		// get d @ integration point
		d = (N * nodal_d)[0]; // 1x1 = 1x4*4x1
		
		gradd = dNdx * nodal_d; // 2x1 = 2x4*4x1
		
		// get H @ integration point
		H = (N * nodal_H)[0]; // 1x1 = 1x4*4x1
		
		// We compute the contribution of the node to Ke
		// prop[0] is gc, prop[1] is lc
		
		dNdx.transpose(dNdx_T);
		N.transpose(N_T);
		
		Ke += det * w *(prop[0]/prop[1]+2. * H) * N_T * N+ // 4x4 = 4x1*1x4
				det * w * prop[0]*prop[1] * dNdx_T * dNdx; // 4x2*2x4
		// We compute the contribution of the node to res
		res += (N_T.getStorage() * det * w * (prop[0]/prop[1] * d -2.*(1.-d)*H)) + // 4x1
				(dNdx_T * gradd * det * w * prop[0]*prop[1]); // 4x2*2x1
	}
}










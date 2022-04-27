/*
 * dispelement.cpp
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


#include "dispelement.hpp"


DispElement::DispElement(Matrix<double> & loc_coordinates, std::vector<double> & loc_d, std::vector<double> & loc_u, std::vector<double> & loc_prop)
{
	coordinates = loc_coordinates;
	nodal_d = loc_d;
	nodal_u = loc_u;
	prop = loc_prop;
	
	dim = 2;
	
	if (coordinates.nbRows()==4) // 4 node elements
	{
		intpt.resize(4,2);
		intpt(0,0) = -1/pow(3,0.5);
		intpt(0,1) = -1/pow(3,0.5);
		intpt(1,0) = 1/pow(3,0.5);
		intpt(1,1) = -1/pow(3,0.5);
		intpt(2,0) = 1/pow(3,0.5);
		intpt(2,1) = 1/pow(3,0.5);
		intpt(3,0) = -1/pow(3,0.5);
		intpt(3,1) = 1/pow(3,0.5);
	}
		
	C.resize(3,3);
	C(0,0) = prop[0]/((1+prop[1]) * (1-2*prop[1])) * (1-prop[1]);
	C(1,1) = prop[0]/((1+prop[1]) * (1-2*prop[1])) * (1-prop[1]);
	C(2,2) = prop[0]/((1+prop[1]) * (1-2*prop[1])) * (1-2*prop[1])/2;
	C(0,1) = prop[0]/((1+prop[1]) * (1-2*prop[1])) * (prop[1]);
	C(1,0) = prop[0]/((1+prop[1]) * (1-2*prop[1])) * (prop[1]);
	
	N.resize(1,coordinates.nbRows()); // 1x4
	N_2d.resize(dim, dim*coordinates.nbRows()); // 2x8
	dNdxi.resize(dim, coordinates.nbRows()); // 2x4
	xi.resize(coordinates.nbRows()); //
	J.resize(dim, dim);// 2X2
	//invJ.resize(dim, dim);// 2X2
	dNdx.resize(dim, coordinates.nbRows());// 2x4
	B.resize((dim-1)*(dim-1)+2, dim*coordinates.nbRows()); // (dim-1)²+2 gives 3 for dim = 2 and 6 form dim = 3 (3x8)
	det = 0.;
	d = 0.;
	w = 1.; // weight in gauss integration
	k = 1e-6; //stabilisation factor
	
	eps.resize(dim);
	sig.resize(dim);
}

void DispElement::GetStiffnessAndRes(Matrix<double> & Ke, std::vector<double> & res)
{
	Ke = 0.;
	std::fill(res.begin(), res.end(), 0.);
	B=0.;
	
	for (UInt i=0; i<intpt.nbRows(); i++) // loop over the integration points
	{
		xi[0] = intpt(i,0);
		xi[1] = intpt(i,1);
		ShapeFun_4lin(dNdxi, N, xi); // evaluates the shape functions at the integration point
		J = dNdxi * coordinates; // 2x2 = 2x4*4x2
		det = J.determinant(); // could be faster is computed "by hand"
		assert(det!=0);
		J.inverse(invJ); // 2x2
		dNdx = invJ * dNdxi; // 2x4 = 2x2*2x4
		
		for (UInt j=0;j<coordinates.nbRows();j++) // loop over N_j (each submatrix in B)
		{
			for (int k=0;k<dim;k++) // fill diagonals of each submatrix
			{
				B(k, k+dim*j) = dNdx(k,j);
			}
			if (dim == 2)
			{
				B(dim, 0) = dNdx(1, j);
				B(dim, 1) = dNdx(0, j);
			}
			else // dim = 3
			{
				 std::cout<<"Error 3D not implemented \n";
				 return;
			}
		}
		
		// get d @ integration point
		d = (N * nodal_d)[0]; // 1x1 = 1x4*4x1
		
		// compute stress
		
		eps = B * nodal_u; // 3x1 = 3x8*8x1
		sig = C*eps; // 3x1 = 3x3*3x1
		
		B.transpose(B_T);
		
		// We compute the contribution of the node to Ke
		Ke += ((((1-d)*(1-d))+k) * det * w) * (B_T * C * B) ; // 8x8 = 8x3*3x3*3x8
		
		// We compute the contribution of the node to res
		res += B_T * sig * (((1-d)*(1-d))+k) * det * w;// 8x1 = 8x3*3x1
	}
}









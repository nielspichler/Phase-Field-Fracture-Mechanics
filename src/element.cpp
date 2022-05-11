
#include "element.hpp"


Element::Element()
{
	
}


void Element::ShapeFun_4lin(Matrix<double> & dNdxi, Matrix<double> & N, std::vector<double> & xi)
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






/*
 * dispelement.hpp
 * 
 * Copyright 2022 student <student@tehpc>
 * k
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


#ifndef DISPELEMENT_HPP
#define DISPELEMENT_HPP

#include "element.hpp"

class DispElement: public Element
{
	public:
		DispElement();
		
		DispElement(Matrix & loc_coordinates, std::vector<double> & loc_d, std::vector<double> & loc_u);
		
		void GetStiffnessAndRes(Matrix & Ke, std::vector<double> & res);
		
	private:
		/* add your private declarations */
		Matrix B;
		Matrix B_T;
		Matrix C;
		Matrix N_2d;
		std::vector<double> eps;
		std::vector<double> sig;
		double k;
};

#endif /* DISPELEMENT_HPP */ 

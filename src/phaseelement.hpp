/*
 * phaseelement.hpp
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


#ifndef PHASEELEMENT_HPP
#define PHASEELEMENT_HPP

#include "element.hpp"

class PhaseElement: public Element
{
	public:
		PhaseElement();
		
		PhaseElement(Matrix & loc_coordinates, std::vector<double> & d, std::vector<double> & H);
		
		// Methods
		void GetStiffnessAndRes(Matrix & Ke, std::vector<double> & res);
		
		
	private:
		// Members
		std::vector<double> gradd;
		
};

#endif /* PHASEELEMENT_HPP */ 

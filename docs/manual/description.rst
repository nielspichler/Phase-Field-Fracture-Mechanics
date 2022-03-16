=============================================
TEHPC Project, Phase-field fracture mechanics
=============================================

Description
===========

This code imlements a finite element phase-field fracture mechanics scheme. The implementation follows mostly the approach proposed in [1]_. 


Objective
=========

The end-goal is to be able to predict the crack propagation path in a brittle linear elastic material for various initial defect location and boundary conditions types. Finite elements are used to model the bulk material response and the phase-field evolution.

Limitations
-----------

For a realisable objective in the time frame dedicated to this implementation, several limitations to the project must be set. The limitations are: 

* The domain is a 2D square
* The mesh used is regular
* Elements are 4-node bilinear elements only
* Only Dirichlet boundary conditions are applied (displacement control)


Theoretical foundation
======================

Energetics
----------

The total potential energy of an elastic body is defined as **Pi** = **U**-**F**, where **U** is the elastic strain energy and **F** the work of external forces. In case a crack is present in the body, the total energy of the body is **Psi** = **Pi** + **Ws** where **Ws** is the energy spent on crack propagation.

Contrary to usual approaches to fracture mechanics, where the crack is seen as a sharp notch, a damage variable *d* is defined on the whole domain and represents the state of damage at every material point. *d* is 1 in the crack and 0 away from it. Along with *d*, a crack density function *gamma*(*d, grad d*) is also defined and used to compute **Ws** on the whole body. 

The strain energy **U** is computed by integrating the strain energy density, weighted by a degradation factor (a function of *d*) such that the strain energy density on the crack is 0. **F** is computed the classical way as the summation of the work of external forces.

The scheme porposed in [1]_ decomposes the problem in two parts. First the the interal energy must be at equilibrium: 

* **U** + **Ws**

Second, the external and internal energy must be at equilibrium: 

* **U**-**F**

In the first step, the strain energy drives the evolution of *d*, in the second step, the boundary conditions drive the evolution of the dicplacement field, affected by *d* through the degradation of the strain energy density field. Then the loop repeats with small increments on the applied boundary conditions.

Finite elements
---------------

The weak form of both problems can be formulated and turned into 2 finite element problem. The mathematical details can be found in [1]_. 

One stifness matrix is computed the phase, the matrix depends on the value of *d* and *H*, a field variable depending on the strain energy (*H* records the maximal strain energy density of the material point in time). The accosiated residue vector depends on the same variables. 

One stifness matrix is computed for the displacements, since the degraded strain energy enters in its formulation, the stifness matrix is directly dependent on *d*. Since only Dirichlet boundary conditions are applied, the residual vector is comprised of the internal forces residues.

Since both stifness matrices are depend on *d*, the element stifness matrices (phase and displacement) are different for each element and need to be computed locally.


Implementation structure
========================

The code for the computaiton of both local stifness matrices is provided in the supplementary folder of [1]_ in the form of a UEL written in Fortran. This code will serve as a base for the implementation of the 2 functions needed to compute the local stifness matrices in c++. A first idea on the code implementaiton is described below.

Functions
---------

d_loc: 
    * input: 
        - 2 material properties Gc, lc
        - 4 coordinates of the element nodes
        - 4 nodal values of d_loc
        - 4 nodal values of H
        - 4 nodal strain energy component (alternatively 12 nodal strain components and the strain energy is computed inside the function)

    * outputs: 
		- local phase stifness matrix
		- local residue vector

u_loc: 
    * input: 
		- 2 material properties E, Young modulus, nu, poisson ratio
		- 4 coordinates of the element nodes
		- 4 nodal values of d_loc
    * outputs: 
    	- local displacement stifness matrix
    	- local internal residue vector (f_int)

Both d_loc and u_loc follow the implementation of the UELs.

A function to evaluate the shape functions

An iterative Newton-Raphson solver


Main
----

Initialize a mesh, i.e. generate a set of coordinates, square domain with quad elements, nnode = # nodes

Initialize field variables H = 0 everywhere, d = 0 everywhere (maybe some gradient is required) and 1 on the crack

Loop in time with a small timestep: 
	* Initialize 2 empty matrices K_u (2*nnode x 2*nnode) and K_d (nnode x nnode)
	* Initialize 2 empty residue vectors r_u (2*nnodes) and r_d (nnodes)
	* Loop over the coordinates:
		- d_loc that outputs the local phase field stifness matrix and residue vector
		- u_loc that outputs the local strain stifness matrix and internal residue vector
		- Both get placed in the right position in K_u and K_d, r_u and r_d with a connectivity table or localization matrix
	* update external loading vector (u_ext + Delta u_ext) 
	* reduce K_u and compute K_u_p*u_ext
	* solve [K]*[u_free;d] = [r_u;r_d]-[K_u_p*u_ext;0] iteratively using Newton-Raphson algorithm.
	* update d and u

References
==========

.. [1] Molnár, Gergely, and Anthony Gravouil. “2D and 3D Abaqus Implementation of a Robust Staggered Phase-Field Solution for Modeling Brittle Fracture.” Finite Elements in Analysis and Design 130 (August 2017): 27–38. https://doi.org/10.1016/j.finel.2017.03.002.

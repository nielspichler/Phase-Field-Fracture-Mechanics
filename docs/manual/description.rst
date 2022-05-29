==============================
Phase-field fracture mechanics
==============================

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

The total potential energy of an elastic body is defined as **:math:`\Pi`** = **:math:`U-F`**, where **:math:`U`** is the elastic strain energy and **F** the work of external forces. In case a crack is present in the body, the total energy of the body is **:math:`\Psi`** = **:math:`\Pi + W_s`** where **:math:`W_s`** is the energy spent on crack propagation.

Contrary to usual approaches to fracture mechanics, where the crack is seen as a sharp notch, a damage variable :math:`d` is defined on the whole domain and represents the state of damage at every material point. :math:`d` is 1 in the crack and 0 away from it. Along with :math:`d`, a crack density function :math:`\gamma (d, \Nabla d)` is also defined and used to compute **:math:`W_s`** on the whole body. 

The strain energy **:math:`U`** is computed by integrating the strain energy density, weighted by a degradation factor (a function of :math:`d`) such that the strain energy density on the crack is 0. **:math:`F`** is computed the classical way as the summation of the work of external forces.

The scheme porposed in [1]_ decomposes the problem in two parts. First the the interal energy must be at equilibrium: 
.. math::
   **U+W_s**

Second, the external and internal energy must be at equilibrium: 
.. math::
   **U-F**

In the first step, the strain energy drives the evolution of *d*, in the second step, the boundary conditions drive the evolution of the dicplacement field, affected by *d* through the degradation of the strain energy density field. Then the loop repeats with small increments on the applied boundary conditions.

Finite elements
---------------

The weak form of both problems can be formulated and turned into 2 finite element problem. The mathematical details can be found in [1]_. 

One stifness matrix is computed the phase, the matrix depends on the value of :math:`d` and :math:`H`, a field variable depending on the strain energy (:math:`H` records the maximal strain energy density of the material point in time). The associated residue vector depends on the same variables. 

One stifness matrix is computed for the displacements, since the degraded strain energy enters in its formulation, the stifness matrix is directly dependent on :math:`d`. Since only Dirichlet boundary conditions are applied, the residual vector is comprised of the internal forces residues.

Since both stifness matrices are depend on :math:`d`, the element stifness matrices (phase and displacement) are different for each element and need to be computed locally.


References
==========

.. [1] Molnár, Gergely, and Anthony Gravouil. “2D and 3D Abaqus Implementation of a Robust Staggered Phase-Field Solution for Modeling Brittle Fracture.” Finite Elements in Analysis and Design 130 (August 2017): 27–38. https://doi.org/10.1016/j.finel.2017.03.002.

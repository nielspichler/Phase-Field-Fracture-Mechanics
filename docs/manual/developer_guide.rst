Developer's Guide
=================

Code architecture
~~~~~~~~~~~~~~~~~


Model class
-----------

The model class take heavy inspiration from the one provided in the course. A constructor builds the model from an input file. Then an assembly method is called that loops over the elements and calls the private method **localStiffness**. This is in this method that the history variable is computed and updated. This method computes for a specific element the tangent stifness matrices, for displacement and phase as well as the corresponding residue vectors. The global tangent stifness matrices and residue vectors are build this way.

Subsequently the displacement tangent stifness matrix is reduced to take into account the Dirichlet boundary conditions in the method **apply_bc**. This method overwrites specific values of the global displacement residue vector with the known/imposed incrmental displacement values, the coressponding row in the matrix is set to 0 with a 1 on the diagonal.

Finally the system is solved. The system is nonlinear therefore an iterative procedure is applied: the system is solved a first time using an LU factorization and the increment in displacement is found and applied. To check convergence the global matrixces and residue vectors are reassembled with the updated field values. Since the incremental displacement values have the imposed values at the boundary conditions due to the first resolition, the **apply_bc** method is used to impose *0* incrmental displacement on the Dirichlet boundary conditions. The magnitude (2-norm) of both residue vectors is computed and should be less than a tolerance when averaged over the node number.

Finally, as one wants to visualize the results, the results are written in different files in an output directory. Two methods **output_nodal** and **output_elemental** are used, both loop over the node or element list and write in a single line, separated by a space the nodel value of the field we want to export. All output files have the same header namely a list of node or element names followed by the x-coordinate and y-coordinate (only for nodes) of the node. Then comes the data, each line is a corresponds to a loading step.

As the model requires the application of the boundary condition to be progressive and works in multiple steps, the above described process is put inside a loop and the total boundary conditions are divided in corresponding steps. This iterative procedure is implemented in the method **iterate** which is the main interface to use the code.


The :cpp:class:`Model` is the main class, it calls all other classes defined in this project. It is the main interface to use the code.

.. doxygenclass:: Model
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:

Element class
-------------

A parent class element is created, this class is fully abstract. Element has all the common members needed for the subclasses and only one private method that computes the valus of the shape functions for a 4 node linear element. 

From this abstract class, 2 subclasses are derived, **PhaseElement** and **DispElement** classes. Both have theis own implementation of the method **GetStiffnessAndRes** which computes the local stifness matrix and local residual. Both implementation could in theory account for other linear element shape and triangular element could be easily implemented in the future.


Elements classes 
''''''''''''''''

The :cpp:class:`Element` is the parent element class, both PhaseElement and DispElement class are subclassed from this one.

.. doxygenclass:: Element
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:

   
The :cpp:class:`DispElement` is the class used to implement a linear elastic element with degraded stifness. 

.. doxygenclass:: DispElement
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:

The :cpp:class:`PhaseElement` is the class used to implement the phase element. 
   
.. doxygenclass:: PhaseElement
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:
   
   
   
Solver class
------------

The class **NLsolver** is a parent class for nonlinear solvers. Only one child class **LU_solver** which is actually a linear solver is used in the code.

.. doxygenclass:: NLsolver
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:

LU_solver
'''''''''

This class performs the LUP factorization of the tangent stifness matrices and is cpoied from `Wikipedia <https://en.wikipedia.org/wiki/LU_decomposition>`_ which provides a `C` code. The main interface is the inherited method **solve** to which we give a system **Ax=b** and solved for **x**.

.. doxygenclass:: LU_solver
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:


Test tools class
----------------

A small class has been implemented to assist testing the class contains utility methody to compare vectors and matrices.

.. doxygenclass:: Test_tools
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:

Provided in the course material
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseMatrix class
----------------

The base matrix and its children class are copied from the project and used as a black-box tool. Some features were added, in particular operator overloading for the **Matrix** class (Matrix += Matrix and double*Matrix). These features were needed to construct the local stifness matrices.


.. doxygenclass:: BaseMatrix
   :members:
   :protected-members:
   :private-members:
   :allow-dot-graphs:


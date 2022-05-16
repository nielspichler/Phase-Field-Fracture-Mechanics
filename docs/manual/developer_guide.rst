Developer's Guide
=================

Code architecture
~~~~~~~~~~~~~~~~~

Element class
-------------

A parent class element is created, this class is fully abstract. Element has all the common members needed for the subclasses and only one private method that computes the valus of the shape functions for a 4 node linear element. 

From this abstract class, 2 subclasses are derived, **PhaseElement** and **DispElement** classes. Both have theis own implementation of the method **GetStiffnessAndRes** which computes the local stifness matrix and local residual. Both implementation could in theory account for other linear element shape and triangular element could be easily implemnted in the future.


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



Model class
-----------

The model class take heavy inspiration from the one provided in the course. A constructor builds the model from an imput file. Then an assembly method is called that loops over the elements and calls the private method **localStiffness**. The global stifness matrix and residue vector are build this way, subsequently the stifness matrix is reduced to take into account the boundary conditions. Finally the system is solved. **The class of solver is not yet designed but most likely will be copied from the course**. Since the phase element requires a history variable to be computed, an **update** method is needed to cumpute this field varible. As one wants to visualize the results, the phase vector is written in a file in an output directory. As the model requires the application of the boundary condition to be progressive and works in multiple steps, the above described process is put inside a loop and the total boundary conditions are divided in corresponding steps. There are no subclasses of this class.


The :cpp:class:`Model` is the main class, it calls all other classes defined in this project. It is the main interface to use the code.

.. doxygenclass:: Model
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


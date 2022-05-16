Getting Started
===============

Obtaining TEHPC Niels Pichler
-----------------------------

Get TEHPC Niels Pichler by cloning it from `gitlab <https://gitlab.ethz.ch>`_::

  > git clone https://gitlab.ethz.ch/npichler/project-tehpc-niels-pichler.git


Requirements for TEHPC Niels Pichler
------------------------------------

The following software are required for TEHPC Niels Pichler:

- `CMake <https://cmake.org/>`_ (3.1.0 or higher)
  
Optional for plotting scripts:

- `Python3 <https://www.python.org/>`_


Compiling TEHPC Niels Pichler
-----------------------------

**Ubuntu-based and macOS systems**:

You can configure and build TEHPC Niels Pichler by following these steps::

  > cd project-tehpc-niels-pichler
  > mkdir build
  > cd build
  > cmake -DCMAKE_BUILD_TYPE:STRING=Release ..
  > make

If you would like to run the tehpc2022 tests as verification::

  > make test

  
Running an example
------------------

Some example simulations are provided in the `project-tehpc-niels-pichler/examples` folder. To run a simulation, you typically proceed as follows::

  > cd build/examples
  > make
  > .basic_example <sim-name> <input-file-name> <output-directory>
  
To reproduce the resultes presented in [1]_ fig.5 do:
  
  > mkdir output
  > ./basic_example sim_paper ../../examples/input_paper.inp output  
    
You can visualize the results with the provided script::

  >  cd ../../python
  >  python3 plotter_paper.py
  
It should produce the following result:

.. image:: figures/Figure_paper.png
   :align: center

  
A 4 element model under similar boundary conditions is also provided, to run it do: 

  > ./basic_example sim_e_4l ../../examples/input_4_el.inp output  






.. [1] Molnár, Gergely, and Anthony Gravouil. “2D and 3D Abaqus Implementation of a Robust Staggered Phase-Field Solution for Modeling Brittle Fracture.” Finite Elements in Analysis and Design 130 (August 2017): 27–38. https://doi.org/10.1016/j.finel.2017.03.002.

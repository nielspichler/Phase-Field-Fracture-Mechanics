# Phase-Field_FE

This project is an implementation of a finite element phase-field fracture mechanics scheme. The approach was successfully implemented in ABAQUS using 2 UEL and a UMAT (10.1016/j.finel.2017.03.002). 

## Getting started

Get Phase-Field_FE by cloning it from [gitlab](https://gitlab.ethz.ch):

    git clone https://gitlab.ethz.ch/npichler/project-tehpc-niels-pichler.git

## Requirements for Phase-Field_FE

The following software are required for Phase-Field_FE:

- [CMake] (https://cmake.org/) (3.1.0 or higher)
  
Optional for plotting scripts:

- [Python3] (https://www.python.org/)

Optional for documentation generation

- [Doxygen 1.8.17] 
- [graphviz]
- [sphinx]
- [breath]

On Linux, in the terminal type: 

    sudo apt-get install doxygen-gui graphviz	
    pip install git+https://github.com/sphinx-doc/sphinx
    pip install breathe


## Compiling Phase-Field_FE

**Ubuntu-based and macOS systems**:

You can configure and build Phase-Field_FE by following these steps::

```
   cd project-tehpc-niels-pichler
   mkdir build
   cd build
   cmake -DCMAKE_BUILD_TYPE:STRING=Release ..
   make
```

## Test and Deploy

```
   make test
```

## Results example

![Alt text](./docs/manual/figures/Illustrations_Readme.png?raw=true "Result example")



## Documentation
To generate the complete documantation
```
   cd project-tehpc-niels-pichler^
   mkdir build
   cd build
   cmake  -DPFFE_DOC:BOOL=ON .. ..
   make
```


## Authors and acknowledgment
Author: Niels Pichler
Help, support and guidance: Prof. David Kammer, Dr. Mohit Pundir, Yaqi Zhao

## License
MIT liscence (Permissive)


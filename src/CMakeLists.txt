# list of header files to compile
set(TEHPC_HEADER
  common.hpp
  base_matrix.hpp
  array.hpp
  array_inline.hpp
  matrix.hpp
  matrix_inline.hpp
  sparse_matrix.hpp
  vector.hpp
  element.hpp
  dispelement.hpp
  phaseelement.hpp
  nonlinear_solver.hpp
  lu_solver.hpp
  newton_raphson_solver.hpp
  test_tools.hpp  
  model.hpp
  )

# list of cpp files to compile
set(TEHPC_SRC
  array.cpp
  matrix.cpp
  element.cpp
  dispelement.cpp
  phaseelement.cpp
  lu_solver.cpp
  newton_raphson_solver.cpp
  test_tools.cpp  
  model.cpp
  )

set(TEHPC_DEPEND_FILES ${TEHPC_SRC} ${TEHPC_HEADER} PARENT_SCOPE)

add_library(Phase-Field_FE ${TEHPC_SRC})

# if linking to other libraries, e.g. MPI
target_link_libraries(Phase-Field_FE)

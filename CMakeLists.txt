cmake_minimum_required(VERSION 3.1)
project(Phase-Field_FE)
enable_language(CXX)

# flags for compilation (options)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17 " CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG " CACHE STRING "" FORCE )

# alternative to add_library (but with option)
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries.")
mark_as_advanced(BUILD_SHARED_LIBS)

# build type
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
  "Build options: None Debug Release RelWithDebInfo MinSizeRel."
  FORCE )
  


# include directories
set(PFFE_INCLUDE_DIRS
  "${CMAKE_CURRENT_BINARY_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  )
include_directories(${PFFE_INCLUDE_DIRS})

option(USE_ARMA "use armadillo" OFF)
if(USE_ARMA)
  find_package(Armadillo REQUIRED)
  include_directories(${ARMADILLO_INCLUDE_DIRS})
endif()

# OPENMP
option(PFFE_USE_OPENMP "Use OPENMP (shared memory)" OFF)
if (PFFE_USE_OPENMP)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
endif (PFFE_USE_OPENMP)

# source directory
add_subdirectory(src)

# ------------------------------------------------------
# Some Macros

option(PFFE_VERBOSE "write extra information to console" OFF)

# examples: define add_simulation function
function(add_simulation SIM_EXE)
  add_executable(${SIM_EXE} ${SIM_EXE}.cpp)
  target_link_libraries(${SIM_EXE} Phase-Field_FE)
endfunction()

# examples: option to de/activate compilation of examples
option(PFFE_EXAMPLES "examples" OFF)
if(PFFE_EXAMPLES)
  add_subdirectory(examples)
endif()

# ------------------------------------------------------
# test
option(PFFE_TESTS "tests" OFF)
if(PFFE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()


# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
option(PFFE_DOC "documentation" OFF)
if(PFFE_DOC)
  add_subdirectory(docs)
endif()

# plotters
add_subdirectory(python)



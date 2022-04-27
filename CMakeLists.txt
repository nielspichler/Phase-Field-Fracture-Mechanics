cmake_minimum_required(VERSION 3.1)
project(tehpc2022)
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
set(TEHPC_INCLUDE_DIRS
  "${CMAKE_CURRENT_BINARY_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  )
include_directories(${TEHPC_INCLUDE_DIRS})

# source directory
add_subdirectory(src)

# ------------------------------------------------------
# Some Macros

# examples: define add_simulation function
function(add_simulation SIM_EXE)
  add_executable(${SIM_EXE} ${SIM_EXE}.cpp)
  target_link_libraries(${SIM_EXE} tehpc2022)
endfunction()

# examples: option to de/activate compilation of examples
option(TEHPC_EXAMPLES "examples" OFF)
if(TEHPC_EXAMPLES)
  add_subdirectory(examples)
endif()

# ------------------------------------------------------
# test
option(TEHPC_TESTS "tests" OFF)
if(TEHPC_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
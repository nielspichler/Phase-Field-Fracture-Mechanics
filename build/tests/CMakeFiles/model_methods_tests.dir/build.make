# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/student/Project_TEHPC/project-tehpc-niels-pichler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/Project_TEHPC/project-tehpc-niels-pichler/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/model_methods_tests.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/model_methods_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/model_methods_tests.dir/flags.make

tests/CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.o: tests/CMakeFiles/model_methods_tests.dir/flags.make
tests/CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.o: ../tests/model_methods_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Project_TEHPC/project-tehpc-niels-pichler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.o"
	cd /home/student/Project_TEHPC/project-tehpc-niels-pichler/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.o -c /home/student/Project_TEHPC/project-tehpc-niels-pichler/tests/model_methods_tests.cpp

tests/CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.i"
	cd /home/student/Project_TEHPC/project-tehpc-niels-pichler/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/student/Project_TEHPC/project-tehpc-niels-pichler/tests/model_methods_tests.cpp > CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.i

tests/CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.s"
	cd /home/student/Project_TEHPC/project-tehpc-niels-pichler/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/student/Project_TEHPC/project-tehpc-niels-pichler/tests/model_methods_tests.cpp -o CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.s

# Object files for target model_methods_tests
model_methods_tests_OBJECTS = \
"CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.o"

# External object files for target model_methods_tests
model_methods_tests_EXTERNAL_OBJECTS =

tests/model_methods_tests: tests/CMakeFiles/model_methods_tests.dir/model_methods_tests.cpp.o
tests/model_methods_tests: tests/CMakeFiles/model_methods_tests.dir/build.make
tests/model_methods_tests: src/libtehpc2022.so
tests/model_methods_tests: tests/CMakeFiles/model_methods_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/student/Project_TEHPC/project-tehpc-niels-pichler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable model_methods_tests"
	cd /home/student/Project_TEHPC/project-tehpc-niels-pichler/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/model_methods_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/model_methods_tests.dir/build: tests/model_methods_tests

.PHONY : tests/CMakeFiles/model_methods_tests.dir/build

tests/CMakeFiles/model_methods_tests.dir/clean:
	cd /home/student/Project_TEHPC/project-tehpc-niels-pichler/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/model_methods_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/model_methods_tests.dir/clean

tests/CMakeFiles/model_methods_tests.dir/depend:
	cd /home/student/Project_TEHPC/project-tehpc-niels-pichler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/Project_TEHPC/project-tehpc-niels-pichler /home/student/Project_TEHPC/project-tehpc-niels-pichler/tests /home/student/Project_TEHPC/project-tehpc-niels-pichler/build /home/student/Project_TEHPC/project-tehpc-niels-pichler/build/tests /home/student/Project_TEHPC/project-tehpc-niels-pichler/build/tests/CMakeFiles/model_methods_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/model_methods_tests.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alida/prog/GallineInFuga

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alida/prog/GallineInFuga/build

# Include any dependencies generated for this target.
include CMakeFiles/Boids.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Boids.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Boids.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Boids.dir/flags.make

CMakeFiles/Boids.dir/src/point.cpp.o: CMakeFiles/Boids.dir/flags.make
CMakeFiles/Boids.dir/src/point.cpp.o: ../src/point.cpp
CMakeFiles/Boids.dir/src/point.cpp.o: CMakeFiles/Boids.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alida/prog/GallineInFuga/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Boids.dir/src/point.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Boids.dir/src/point.cpp.o -MF CMakeFiles/Boids.dir/src/point.cpp.o.d -o CMakeFiles/Boids.dir/src/point.cpp.o -c /home/alida/prog/GallineInFuga/src/point.cpp

CMakeFiles/Boids.dir/src/point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boids.dir/src/point.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alida/prog/GallineInFuga/src/point.cpp > CMakeFiles/Boids.dir/src/point.cpp.i

CMakeFiles/Boids.dir/src/point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boids.dir/src/point.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alida/prog/GallineInFuga/src/point.cpp -o CMakeFiles/Boids.dir/src/point.cpp.s

CMakeFiles/Boids.dir/src/boid.cpp.o: CMakeFiles/Boids.dir/flags.make
CMakeFiles/Boids.dir/src/boid.cpp.o: ../src/boid.cpp
CMakeFiles/Boids.dir/src/boid.cpp.o: CMakeFiles/Boids.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alida/prog/GallineInFuga/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Boids.dir/src/boid.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Boids.dir/src/boid.cpp.o -MF CMakeFiles/Boids.dir/src/boid.cpp.o.d -o CMakeFiles/Boids.dir/src/boid.cpp.o -c /home/alida/prog/GallineInFuga/src/boid.cpp

CMakeFiles/Boids.dir/src/boid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boids.dir/src/boid.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alida/prog/GallineInFuga/src/boid.cpp > CMakeFiles/Boids.dir/src/boid.cpp.i

CMakeFiles/Boids.dir/src/boid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boids.dir/src/boid.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alida/prog/GallineInFuga/src/boid.cpp -o CMakeFiles/Boids.dir/src/boid.cpp.s

CMakeFiles/Boids.dir/src/quadtree.cpp.o: CMakeFiles/Boids.dir/flags.make
CMakeFiles/Boids.dir/src/quadtree.cpp.o: ../src/quadtree.cpp
CMakeFiles/Boids.dir/src/quadtree.cpp.o: CMakeFiles/Boids.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alida/prog/GallineInFuga/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Boids.dir/src/quadtree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Boids.dir/src/quadtree.cpp.o -MF CMakeFiles/Boids.dir/src/quadtree.cpp.o.d -o CMakeFiles/Boids.dir/src/quadtree.cpp.o -c /home/alida/prog/GallineInFuga/src/quadtree.cpp

CMakeFiles/Boids.dir/src/quadtree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boids.dir/src/quadtree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alida/prog/GallineInFuga/src/quadtree.cpp > CMakeFiles/Boids.dir/src/quadtree.cpp.i

CMakeFiles/Boids.dir/src/quadtree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boids.dir/src/quadtree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alida/prog/GallineInFuga/src/quadtree.cpp -o CMakeFiles/Boids.dir/src/quadtree.cpp.s

CMakeFiles/Boids.dir/src/simulation.cpp.o: CMakeFiles/Boids.dir/flags.make
CMakeFiles/Boids.dir/src/simulation.cpp.o: ../src/simulation.cpp
CMakeFiles/Boids.dir/src/simulation.cpp.o: CMakeFiles/Boids.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alida/prog/GallineInFuga/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Boids.dir/src/simulation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Boids.dir/src/simulation.cpp.o -MF CMakeFiles/Boids.dir/src/simulation.cpp.o.d -o CMakeFiles/Boids.dir/src/simulation.cpp.o -c /home/alida/prog/GallineInFuga/src/simulation.cpp

CMakeFiles/Boids.dir/src/simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boids.dir/src/simulation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alida/prog/GallineInFuga/src/simulation.cpp > CMakeFiles/Boids.dir/src/simulation.cpp.i

CMakeFiles/Boids.dir/src/simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boids.dir/src/simulation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alida/prog/GallineInFuga/src/simulation.cpp -o CMakeFiles/Boids.dir/src/simulation.cpp.s

CMakeFiles/Boids.dir/src/sfml.cpp.o: CMakeFiles/Boids.dir/flags.make
CMakeFiles/Boids.dir/src/sfml.cpp.o: ../src/sfml.cpp
CMakeFiles/Boids.dir/src/sfml.cpp.o: CMakeFiles/Boids.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alida/prog/GallineInFuga/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Boids.dir/src/sfml.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Boids.dir/src/sfml.cpp.o -MF CMakeFiles/Boids.dir/src/sfml.cpp.o.d -o CMakeFiles/Boids.dir/src/sfml.cpp.o -c /home/alida/prog/GallineInFuga/src/sfml.cpp

CMakeFiles/Boids.dir/src/sfml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Boids.dir/src/sfml.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alida/prog/GallineInFuga/src/sfml.cpp > CMakeFiles/Boids.dir/src/sfml.cpp.i

CMakeFiles/Boids.dir/src/sfml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Boids.dir/src/sfml.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alida/prog/GallineInFuga/src/sfml.cpp -o CMakeFiles/Boids.dir/src/sfml.cpp.s

# Object files for target Boids
Boids_OBJECTS = \
"CMakeFiles/Boids.dir/src/point.cpp.o" \
"CMakeFiles/Boids.dir/src/boid.cpp.o" \
"CMakeFiles/Boids.dir/src/quadtree.cpp.o" \
"CMakeFiles/Boids.dir/src/simulation.cpp.o" \
"CMakeFiles/Boids.dir/src/sfml.cpp.o"

# External object files for target Boids
Boids_EXTERNAL_OBJECTS =

Boids: CMakeFiles/Boids.dir/src/point.cpp.o
Boids: CMakeFiles/Boids.dir/src/boid.cpp.o
Boids: CMakeFiles/Boids.dir/src/quadtree.cpp.o
Boids: CMakeFiles/Boids.dir/src/simulation.cpp.o
Boids: CMakeFiles/Boids.dir/src/sfml.cpp.o
Boids: CMakeFiles/Boids.dir/build.make
Boids: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
Boids: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
Boids: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
Boids: CMakeFiles/Boids.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alida/prog/GallineInFuga/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable Boids"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Boids.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Boids.dir/build: Boids
.PHONY : CMakeFiles/Boids.dir/build

CMakeFiles/Boids.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Boids.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Boids.dir/clean

CMakeFiles/Boids.dir/depend:
	cd /home/alida/prog/GallineInFuga/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alida/prog/GallineInFuga /home/alida/prog/GallineInFuga /home/alida/prog/GallineInFuga/build /home/alida/prog/GallineInFuga/build /home/alida/prog/GallineInFuga/build/CMakeFiles/Boids.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Boids.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dan/workspace/367_p2_LightAndMovement

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dan/workspace/367_p2_LightAndMovement/build

# Include any dependencies generated for this target.
include CMakeFiles/sample.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sample.dir/flags.make

CMakeFiles/sample.dir/animation.cc.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/animation.cc.o: ../animation.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/animation.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/animation.cc.o -c /home/dan/workspace/367_p2_LightAndMovement/animation.cc

CMakeFiles/sample.dir/animation.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/animation.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/animation.cc > CMakeFiles/sample.dir/animation.cc.i

CMakeFiles/sample.dir/animation.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/animation.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/animation.cc -o CMakeFiles/sample.dir/animation.cc.s

CMakeFiles/sample.dir/animation.cc.o.requires:
.PHONY : CMakeFiles/sample.dir/animation.cc.o.requires

CMakeFiles/sample.dir/animation.cc.o.provides: CMakeFiles/sample.dir/animation.cc.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/animation.cc.o.provides.build
.PHONY : CMakeFiles/sample.dir/animation.cc.o.provides

CMakeFiles/sample.dir/animation.cc.o.provides.build: CMakeFiles/sample.dir/animation.cc.o

CMakeFiles/sample.dir/StreetLight.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/StreetLight.cpp.o: ../StreetLight.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/StreetLight.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/StreetLight.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/StreetLight.cpp

CMakeFiles/sample.dir/StreetLight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/StreetLight.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/StreetLight.cpp > CMakeFiles/sample.dir/StreetLight.cpp.i

CMakeFiles/sample.dir/StreetLight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/StreetLight.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/StreetLight.cpp -o CMakeFiles/sample.dir/StreetLight.cpp.s

CMakeFiles/sample.dir/StreetLight.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/StreetLight.cpp.o.requires

CMakeFiles/sample.dir/StreetLight.cpp.o.provides: CMakeFiles/sample.dir/StreetLight.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/StreetLight.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/StreetLight.cpp.o.provides

CMakeFiles/sample.dir/StreetLight.cpp.o.provides.build: CMakeFiles/sample.dir/StreetLight.cpp.o

CMakeFiles/sample.dir/Island.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Island.cpp.o: ../Island.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Island.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Island.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Island.cpp

CMakeFiles/sample.dir/Island.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Island.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Island.cpp > CMakeFiles/sample.dir/Island.cpp.i

CMakeFiles/sample.dir/Island.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Island.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Island.cpp -o CMakeFiles/sample.dir/Island.cpp.s

CMakeFiles/sample.dir/Island.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Island.cpp.o.requires

CMakeFiles/sample.dir/Island.cpp.o.provides: CMakeFiles/sample.dir/Island.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Island.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Island.cpp.o.provides

CMakeFiles/sample.dir/Island.cpp.o.provides.build: CMakeFiles/sample.dir/Island.cpp.o

CMakeFiles/sample.dir/UFO.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/UFO.cpp.o: ../UFO.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/UFO.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/UFO.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/UFO.cpp

CMakeFiles/sample.dir/UFO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/UFO.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/UFO.cpp > CMakeFiles/sample.dir/UFO.cpp.i

CMakeFiles/sample.dir/UFO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/UFO.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/UFO.cpp -o CMakeFiles/sample.dir/UFO.cpp.s

CMakeFiles/sample.dir/UFO.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/UFO.cpp.o.requires

CMakeFiles/sample.dir/UFO.cpp.o.provides: CMakeFiles/sample.dir/UFO.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/UFO.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/UFO.cpp.o.provides

CMakeFiles/sample.dir/UFO.cpp.o.provides.build: CMakeFiles/sample.dir/UFO.cpp.o

CMakeFiles/sample.dir/Tire.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Tire.cpp.o: ../Tire.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Tire.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Tire.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Tire.cpp

CMakeFiles/sample.dir/Tire.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Tire.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Tire.cpp > CMakeFiles/sample.dir/Tire.cpp.i

CMakeFiles/sample.dir/Tire.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Tire.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Tire.cpp -o CMakeFiles/sample.dir/Tire.cpp.s

CMakeFiles/sample.dir/Tire.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Tire.cpp.o.requires

CMakeFiles/sample.dir/Tire.cpp.o.provides: CMakeFiles/sample.dir/Tire.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Tire.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Tire.cpp.o.provides

CMakeFiles/sample.dir/Tire.cpp.o.provides.build: CMakeFiles/sample.dir/Tire.cpp.o

CMakeFiles/sample.dir/WeatherVaneBase.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/WeatherVaneBase.cpp.o: ../WeatherVaneBase.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/WeatherVaneBase.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/WeatherVaneBase.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/WeatherVaneBase.cpp

CMakeFiles/sample.dir/WeatherVaneBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/WeatherVaneBase.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/WeatherVaneBase.cpp > CMakeFiles/sample.dir/WeatherVaneBase.cpp.i

CMakeFiles/sample.dir/WeatherVaneBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/WeatherVaneBase.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/WeatherVaneBase.cpp -o CMakeFiles/sample.dir/WeatherVaneBase.cpp.s

CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.requires

CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.provides: CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.provides

CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.provides.build: CMakeFiles/sample.dir/WeatherVaneBase.cpp.o

CMakeFiles/sample.dir/VaneSwivel.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/VaneSwivel.cpp.o: ../VaneSwivel.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/VaneSwivel.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/VaneSwivel.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/VaneSwivel.cpp

CMakeFiles/sample.dir/VaneSwivel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/VaneSwivel.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/VaneSwivel.cpp > CMakeFiles/sample.dir/VaneSwivel.cpp.i

CMakeFiles/sample.dir/VaneSwivel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/VaneSwivel.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/VaneSwivel.cpp -o CMakeFiles/sample.dir/VaneSwivel.cpp.s

CMakeFiles/sample.dir/VaneSwivel.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/VaneSwivel.cpp.o.requires

CMakeFiles/sample.dir/VaneSwivel.cpp.o.provides: CMakeFiles/sample.dir/VaneSwivel.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/VaneSwivel.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/VaneSwivel.cpp.o.provides

CMakeFiles/sample.dir/VaneSwivel.cpp.o.provides.build: CMakeFiles/sample.dir/VaneSwivel.cpp.o

CMakeFiles/sample.dir/Car.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Car.cpp.o: ../Car.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Car.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Car.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Car.cpp

CMakeFiles/sample.dir/Car.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Car.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Car.cpp > CMakeFiles/sample.dir/Car.cpp.i

CMakeFiles/sample.dir/Car.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Car.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Car.cpp -o CMakeFiles/sample.dir/Car.cpp.s

CMakeFiles/sample.dir/Car.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Car.cpp.o.requires

CMakeFiles/sample.dir/Car.cpp.o.provides: CMakeFiles/sample.dir/Car.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Car.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Car.cpp.o.provides

CMakeFiles/sample.dir/Car.cpp.o.provides.build: CMakeFiles/sample.dir/Car.cpp.o

CMakeFiles/sample.dir/Ground.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Ground.cpp.o: ../Ground.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Ground.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Ground.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Ground.cpp

CMakeFiles/sample.dir/Ground.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Ground.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Ground.cpp > CMakeFiles/sample.dir/Ground.cpp.i

CMakeFiles/sample.dir/Ground.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Ground.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Ground.cpp -o CMakeFiles/sample.dir/Ground.cpp.s

CMakeFiles/sample.dir/Ground.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Ground.cpp.o.requires

CMakeFiles/sample.dir/Ground.cpp.o.provides: CMakeFiles/sample.dir/Ground.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Ground.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Ground.cpp.o.provides

CMakeFiles/sample.dir/Ground.cpp.o.provides.build: CMakeFiles/sample.dir/Ground.cpp.o

CMakeFiles/sample.dir/Shapes/Sphere.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Shapes/Sphere.cpp.o: ../Shapes/Sphere.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Shapes/Sphere.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Shapes/Sphere.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Shapes/Sphere.cpp

CMakeFiles/sample.dir/Shapes/Sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Shapes/Sphere.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Shapes/Sphere.cpp > CMakeFiles/sample.dir/Shapes/Sphere.cpp.i

CMakeFiles/sample.dir/Shapes/Sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Shapes/Sphere.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Shapes/Sphere.cpp -o CMakeFiles/sample.dir/Shapes/Sphere.cpp.s

CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.requires

CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.provides: CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.provides

CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.provides.build: CMakeFiles/sample.dir/Shapes/Sphere.cpp.o

CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o: ../Shapes/Cylinder.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Shapes/Cylinder.cpp

CMakeFiles/sample.dir/Shapes/Cylinder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Shapes/Cylinder.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Shapes/Cylinder.cpp > CMakeFiles/sample.dir/Shapes/Cylinder.cpp.i

CMakeFiles/sample.dir/Shapes/Cylinder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Shapes/Cylinder.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Shapes/Cylinder.cpp -o CMakeFiles/sample.dir/Shapes/Cylinder.cpp.s

CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.requires

CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.provides: CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.provides

CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.provides.build: CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o

CMakeFiles/sample.dir/Shapes/Torus.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Shapes/Torus.cpp.o: ../Shapes/Torus.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Shapes/Torus.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Shapes/Torus.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Shapes/Torus.cpp

CMakeFiles/sample.dir/Shapes/Torus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Shapes/Torus.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Shapes/Torus.cpp > CMakeFiles/sample.dir/Shapes/Torus.cpp.i

CMakeFiles/sample.dir/Shapes/Torus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Shapes/Torus.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Shapes/Torus.cpp -o CMakeFiles/sample.dir/Shapes/Torus.cpp.s

CMakeFiles/sample.dir/Shapes/Torus.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Shapes/Torus.cpp.o.requires

CMakeFiles/sample.dir/Shapes/Torus.cpp.o.provides: CMakeFiles/sample.dir/Shapes/Torus.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Shapes/Torus.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Shapes/Torus.cpp.o.provides

CMakeFiles/sample.dir/Shapes/Torus.cpp.o.provides.build: CMakeFiles/sample.dir/Shapes/Torus.cpp.o

CMakeFiles/sample.dir/Shapes/Fan.cpp.o: CMakeFiles/sample.dir/flags.make
CMakeFiles/sample.dir/Shapes/Fan.cpp.o: ../Shapes/Fan.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample.dir/Shapes/Fan.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample.dir/Shapes/Fan.cpp.o -c /home/dan/workspace/367_p2_LightAndMovement/Shapes/Fan.cpp

CMakeFiles/sample.dir/Shapes/Fan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample.dir/Shapes/Fan.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dan/workspace/367_p2_LightAndMovement/Shapes/Fan.cpp > CMakeFiles/sample.dir/Shapes/Fan.cpp.i

CMakeFiles/sample.dir/Shapes/Fan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample.dir/Shapes/Fan.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dan/workspace/367_p2_LightAndMovement/Shapes/Fan.cpp -o CMakeFiles/sample.dir/Shapes/Fan.cpp.s

CMakeFiles/sample.dir/Shapes/Fan.cpp.o.requires:
.PHONY : CMakeFiles/sample.dir/Shapes/Fan.cpp.o.requires

CMakeFiles/sample.dir/Shapes/Fan.cpp.o.provides: CMakeFiles/sample.dir/Shapes/Fan.cpp.o.requires
	$(MAKE) -f CMakeFiles/sample.dir/build.make CMakeFiles/sample.dir/Shapes/Fan.cpp.o.provides.build
.PHONY : CMakeFiles/sample.dir/Shapes/Fan.cpp.o.provides

CMakeFiles/sample.dir/Shapes/Fan.cpp.o.provides.build: CMakeFiles/sample.dir/Shapes/Fan.cpp.o

# Object files for target sample
sample_OBJECTS = \
"CMakeFiles/sample.dir/animation.cc.o" \
"CMakeFiles/sample.dir/StreetLight.cpp.o" \
"CMakeFiles/sample.dir/Island.cpp.o" \
"CMakeFiles/sample.dir/UFO.cpp.o" \
"CMakeFiles/sample.dir/Tire.cpp.o" \
"CMakeFiles/sample.dir/WeatherVaneBase.cpp.o" \
"CMakeFiles/sample.dir/VaneSwivel.cpp.o" \
"CMakeFiles/sample.dir/Car.cpp.o" \
"CMakeFiles/sample.dir/Ground.cpp.o" \
"CMakeFiles/sample.dir/Shapes/Sphere.cpp.o" \
"CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o" \
"CMakeFiles/sample.dir/Shapes/Torus.cpp.o" \
"CMakeFiles/sample.dir/Shapes/Fan.cpp.o"

# External object files for target sample
sample_EXTERNAL_OBJECTS =

sample: CMakeFiles/sample.dir/animation.cc.o
sample: CMakeFiles/sample.dir/StreetLight.cpp.o
sample: CMakeFiles/sample.dir/Island.cpp.o
sample: CMakeFiles/sample.dir/UFO.cpp.o
sample: CMakeFiles/sample.dir/Tire.cpp.o
sample: CMakeFiles/sample.dir/WeatherVaneBase.cpp.o
sample: CMakeFiles/sample.dir/VaneSwivel.cpp.o
sample: CMakeFiles/sample.dir/Car.cpp.o
sample: CMakeFiles/sample.dir/Ground.cpp.o
sample: CMakeFiles/sample.dir/Shapes/Sphere.cpp.o
sample: CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o
sample: CMakeFiles/sample.dir/Shapes/Torus.cpp.o
sample: CMakeFiles/sample.dir/Shapes/Fan.cpp.o
sample: CMakeFiles/sample.dir/build.make
sample: /usr/local/lib/libglfw3.a
sample: /usr/lib/x86_64-linux-gnu/libGLU.so
sample: /usr/lib/x86_64-linux-gnu/libGL.so
sample: /usr/lib/x86_64-linux-gnu/libSM.so
sample: /usr/lib/x86_64-linux-gnu/libICE.so
sample: /usr/lib/x86_64-linux-gnu/libX11.so
sample: /usr/lib/x86_64-linux-gnu/libXext.so
sample: /usr/lib/x86_64-linux-gnu/libGLEW.so
sample: /usr/lib/x86_64-linux-gnu/libGLU.so
sample: /usr/lib/x86_64-linux-gnu/libGL.so
sample: /usr/lib/x86_64-linux-gnu/libSM.so
sample: /usr/lib/x86_64-linux-gnu/libICE.so
sample: /usr/lib/x86_64-linux-gnu/libX11.so
sample: /usr/lib/x86_64-linux-gnu/libXext.so
sample: /usr/local/lib/libglfw3.a
sample: /usr/lib/x86_64-linux-gnu/libGLEW.so
sample: CMakeFiles/sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sample.dir/build: sample
.PHONY : CMakeFiles/sample.dir/build

CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/animation.cc.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/StreetLight.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Island.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/UFO.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Tire.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/WeatherVaneBase.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/VaneSwivel.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Car.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Ground.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Shapes/Sphere.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Shapes/Cylinder.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Shapes/Torus.cpp.o.requires
CMakeFiles/sample.dir/requires: CMakeFiles/sample.dir/Shapes/Fan.cpp.o.requires
.PHONY : CMakeFiles/sample.dir/requires

CMakeFiles/sample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sample.dir/clean

CMakeFiles/sample.dir/depend:
	cd /home/dan/workspace/367_p2_LightAndMovement/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dan/workspace/367_p2_LightAndMovement /home/dan/workspace/367_p2_LightAndMovement /home/dan/workspace/367_p2_LightAndMovement/build /home/dan/workspace/367_p2_LightAndMovement/build /home/dan/workspace/367_p2_LightAndMovement/build/CMakeFiles/sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sample.dir/depend


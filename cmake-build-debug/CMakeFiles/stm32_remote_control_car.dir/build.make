# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /snap/clion/152/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/152/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/carlosrodrigues/Arduino/stm32-remote-control-car

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/carlosrodrigues/Arduino/stm32-remote-control-car/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/stm32_remote_control_car.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stm32_remote_control_car.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stm32_remote_control_car.dir/flags.make

CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.o: CMakeFiles/stm32_remote_control_car.dir/flags.make
CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.o: ../gamepad.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carlosrodrigues/Arduino/stm32-remote-control-car/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.o -c /home/carlosrodrigues/Arduino/stm32-remote-control-car/gamepad.cpp

CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carlosrodrigues/Arduino/stm32-remote-control-car/gamepad.cpp > CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.i

CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carlosrodrigues/Arduino/stm32-remote-control-car/gamepad.cpp -o CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.s

# Object files for target stm32_remote_control_car
stm32_remote_control_car_OBJECTS = \
"CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.o"

# External object files for target stm32_remote_control_car
stm32_remote_control_car_EXTERNAL_OBJECTS =

stm32_remote_control_car: CMakeFiles/stm32_remote_control_car.dir/gamepad.cpp.o
stm32_remote_control_car: CMakeFiles/stm32_remote_control_car.dir/build.make
stm32_remote_control_car: CMakeFiles/stm32_remote_control_car.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/carlosrodrigues/Arduino/stm32-remote-control-car/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stm32_remote_control_car"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stm32_remote_control_car.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stm32_remote_control_car.dir/build: stm32_remote_control_car

.PHONY : CMakeFiles/stm32_remote_control_car.dir/build

CMakeFiles/stm32_remote_control_car.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stm32_remote_control_car.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stm32_remote_control_car.dir/clean

CMakeFiles/stm32_remote_control_car.dir/depend:
	cd /home/carlosrodrigues/Arduino/stm32-remote-control-car/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carlosrodrigues/Arduino/stm32-remote-control-car /home/carlosrodrigues/Arduino/stm32-remote-control-car /home/carlosrodrigues/Arduino/stm32-remote-control-car/cmake-build-debug /home/carlosrodrigues/Arduino/stm32-remote-control-car/cmake-build-debug /home/carlosrodrigues/Arduino/stm32-remote-control-car/cmake-build-debug/CMakeFiles/stm32_remote_control_car.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stm32_remote_control_car.dir/depend


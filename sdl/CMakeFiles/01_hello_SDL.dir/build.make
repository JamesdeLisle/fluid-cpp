# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/james/prog/cell/exp/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/james/prog/cell/exp/cpp

# Include any dependencies generated for this target.
include CMakeFiles/01_hello_SDL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/01_hello_SDL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/01_hello_SDL.dir/flags.make

CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o: CMakeFiles/01_hello_SDL.dir/flags.make
CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o: 01_hello_SDL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/james/prog/cell/exp/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o -c /home/james/prog/cell/exp/cpp/01_hello_SDL.cpp

CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/james/prog/cell/exp/cpp/01_hello_SDL.cpp > CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.i

CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/james/prog/cell/exp/cpp/01_hello_SDL.cpp -o CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.s

CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.requires:

.PHONY : CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.requires

CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.provides: CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.requires
	$(MAKE) -f CMakeFiles/01_hello_SDL.dir/build.make CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.provides.build
.PHONY : CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.provides

CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.provides.build: CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o


# Object files for target 01_hello_SDL
01_hello_SDL_OBJECTS = \
"CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o"

# External object files for target 01_hello_SDL
01_hello_SDL_EXTERNAL_OBJECTS =

01_hello_SDL: CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o
01_hello_SDL: CMakeFiles/01_hello_SDL.dir/build.make
01_hello_SDL: CMakeFiles/01_hello_SDL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/james/prog/cell/exp/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 01_hello_SDL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/01_hello_SDL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/01_hello_SDL.dir/build: 01_hello_SDL

.PHONY : CMakeFiles/01_hello_SDL.dir/build

CMakeFiles/01_hello_SDL.dir/requires: CMakeFiles/01_hello_SDL.dir/01_hello_SDL.cpp.o.requires

.PHONY : CMakeFiles/01_hello_SDL.dir/requires

CMakeFiles/01_hello_SDL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/01_hello_SDL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/01_hello_SDL.dir/clean

CMakeFiles/01_hello_SDL.dir/depend:
	cd /home/james/prog/cell/exp/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/james/prog/cell/exp/cpp /home/james/prog/cell/exp/cpp /home/james/prog/cell/exp/cpp /home/james/prog/cell/exp/cpp /home/james/prog/cell/exp/cpp/CMakeFiles/01_hello_SDL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/01_hello_SDL.dir/depend

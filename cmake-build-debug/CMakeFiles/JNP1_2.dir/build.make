# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/badochov/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/badochov/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/badochov/Desktop/JNP/JNP1_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/badochov/Desktop/JNP/JNP1_2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/JNP1_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/JNP1_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/JNP1_2.dir/flags.make

CMakeFiles/JNP1_2.dir/encstrset.cc.o: CMakeFiles/JNP1_2.dir/flags.make
CMakeFiles/JNP1_2.dir/encstrset.cc.o: ../encstrset.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/badochov/Desktop/JNP/JNP1_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/JNP1_2.dir/encstrset.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/JNP1_2.dir/encstrset.cc.o -c /home/badochov/Desktop/JNP/JNP1_2/encstrset.cc

CMakeFiles/JNP1_2.dir/encstrset.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JNP1_2.dir/encstrset.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/badochov/Desktop/JNP/JNP1_2/encstrset.cc > CMakeFiles/JNP1_2.dir/encstrset.cc.i

CMakeFiles/JNP1_2.dir/encstrset.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JNP1_2.dir/encstrset.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/badochov/Desktop/JNP/JNP1_2/encstrset.cc -o CMakeFiles/JNP1_2.dir/encstrset.cc.s

# Object files for target JNP1_2
JNP1_2_OBJECTS = \
"CMakeFiles/JNP1_2.dir/encstrset.cc.o"

# External object files for target JNP1_2
JNP1_2_EXTERNAL_OBJECTS =

JNP1_2: CMakeFiles/JNP1_2.dir/encstrset.cc.o
JNP1_2: CMakeFiles/JNP1_2.dir/build.make
JNP1_2: CMakeFiles/JNP1_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/badochov/Desktop/JNP/JNP1_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable JNP1_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JNP1_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/JNP1_2.dir/build: JNP1_2

.PHONY : CMakeFiles/JNP1_2.dir/build

CMakeFiles/JNP1_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/JNP1_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/JNP1_2.dir/clean

CMakeFiles/JNP1_2.dir/depend:
	cd /home/badochov/Desktop/JNP/JNP1_2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/badochov/Desktop/JNP/JNP1_2 /home/badochov/Desktop/JNP/JNP1_2 /home/badochov/Desktop/JNP/JNP1_2/cmake-build-debug /home/badochov/Desktop/JNP/JNP1_2/cmake-build-debug /home/badochov/Desktop/JNP/JNP1_2/cmake-build-debug/CMakeFiles/JNP1_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/JNP1_2.dir/depend


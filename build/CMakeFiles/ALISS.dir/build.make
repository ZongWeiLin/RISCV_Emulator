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
CMAKE_SOURCE_DIR = /home/wei/git_repos/RISCV_Emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wei/git_repos/RISCV_Emulator/build

# Include any dependencies generated for this target.
include CMakeFiles/ALISS.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ALISS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ALISS.dir/flags.make

CMakeFiles/ALISS.dir/src/ALISS.cpp.o: CMakeFiles/ALISS.dir/flags.make
CMakeFiles/ALISS.dir/src/ALISS.cpp.o: ../src/ALISS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wei/git_repos/RISCV_Emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ALISS.dir/src/ALISS.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ALISS.dir/src/ALISS.cpp.o -c /home/wei/git_repos/RISCV_Emulator/src/ALISS.cpp

CMakeFiles/ALISS.dir/src/ALISS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALISS.dir/src/ALISS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wei/git_repos/RISCV_Emulator/src/ALISS.cpp > CMakeFiles/ALISS.dir/src/ALISS.cpp.i

CMakeFiles/ALISS.dir/src/ALISS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALISS.dir/src/ALISS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wei/git_repos/RISCV_Emulator/src/ALISS.cpp -o CMakeFiles/ALISS.dir/src/ALISS.cpp.s

CMakeFiles/ALISS.dir/src/main.cpp.o: CMakeFiles/ALISS.dir/flags.make
CMakeFiles/ALISS.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wei/git_repos/RISCV_Emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ALISS.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ALISS.dir/src/main.cpp.o -c /home/wei/git_repos/RISCV_Emulator/src/main.cpp

CMakeFiles/ALISS.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALISS.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wei/git_repos/RISCV_Emulator/src/main.cpp > CMakeFiles/ALISS.dir/src/main.cpp.i

CMakeFiles/ALISS.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALISS.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wei/git_repos/RISCV_Emulator/src/main.cpp -o CMakeFiles/ALISS.dir/src/main.cpp.s

# Object files for target ALISS
ALISS_OBJECTS = \
"CMakeFiles/ALISS.dir/src/ALISS.cpp.o" \
"CMakeFiles/ALISS.dir/src/main.cpp.o"

# External object files for target ALISS
ALISS_EXTERNAL_OBJECTS =

ALISS: CMakeFiles/ALISS.dir/src/ALISS.cpp.o
ALISS: CMakeFiles/ALISS.dir/src/main.cpp.o
ALISS: CMakeFiles/ALISS.dir/build.make
ALISS: CMakeFiles/ALISS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wei/git_repos/RISCV_Emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ALISS"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ALISS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ALISS.dir/build: ALISS

.PHONY : CMakeFiles/ALISS.dir/build

CMakeFiles/ALISS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ALISS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ALISS.dir/clean

CMakeFiles/ALISS.dir/depend:
	cd /home/wei/git_repos/RISCV_Emulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wei/git_repos/RISCV_Emulator /home/wei/git_repos/RISCV_Emulator /home/wei/git_repos/RISCV_Emulator/build /home/wei/git_repos/RISCV_Emulator/build /home/wei/git_repos/RISCV_Emulator/build/CMakeFiles/ALISS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ALISS.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/92/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/92/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mike/CLionProjects/mikecraft

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mike/CLionProjects/mikecraft/cmake-build-debug

# Include any dependencies generated for this target.
include includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/depend.make

# Include the progress variables for this target.
include includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/progress.make

# Include the compile flags for this target's objects.
include includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/flags.make

includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o: includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/flags.make
includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o: ../includes/glew-2.1.0/src/glewinfo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o"
	cd /home/mike/CLionProjects/mikecraft/cmake-build-debug/includes/glew-2.1.0/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o   -c /home/mike/CLionProjects/mikecraft/includes/glew-2.1.0/src/glewinfo.c

includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.i"
	cd /home/mike/CLionProjects/mikecraft/cmake-build-debug/includes/glew-2.1.0/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mike/CLionProjects/mikecraft/includes/glew-2.1.0/src/glewinfo.c > CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.i

includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.s"
	cd /home/mike/CLionProjects/mikecraft/cmake-build-debug/includes/glew-2.1.0/build/cmake && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mike/CLionProjects/mikecraft/includes/glew-2.1.0/src/glewinfo.c -o CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.s

# Object files for target glewinfo
glewinfo_OBJECTS = \
"CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o"

# External object files for target glewinfo
glewinfo_EXTERNAL_OBJECTS =

bin/glewinfo: includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/__/__/src/glewinfo.c.o
bin/glewinfo: includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/build.make
bin/glewinfo: lib/libGLEWd.so.2.1.0
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libSM.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libICE.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libX11.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libXext.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libGL.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/glewinfo: includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../../bin/glewinfo"
	cd /home/mike/CLionProjects/mikecraft/cmake-build-debug/includes/glew-2.1.0/build/cmake && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glewinfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/build: bin/glewinfo

.PHONY : includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/build

includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/clean:
	cd /home/mike/CLionProjects/mikecraft/cmake-build-debug/includes/glew-2.1.0/build/cmake && $(CMAKE_COMMAND) -P CMakeFiles/glewinfo.dir/cmake_clean.cmake
.PHONY : includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/clean

includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/depend:
	cd /home/mike/CLionProjects/mikecraft/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mike/CLionProjects/mikecraft /home/mike/CLionProjects/mikecraft/includes/glew-2.1.0/build/cmake /home/mike/CLionProjects/mikecraft/cmake-build-debug /home/mike/CLionProjects/mikecraft/cmake-build-debug/includes/glew-2.1.0/build/cmake /home/mike/CLionProjects/mikecraft/cmake-build-debug/includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : includes/glew-2.1.0/build/cmake/CMakeFiles/glewinfo.dir/depend


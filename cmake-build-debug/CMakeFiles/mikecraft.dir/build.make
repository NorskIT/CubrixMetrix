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
CMAKE_COMMAND = /snap/clion/98/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/98/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mike/CLionProjects/mikecraft

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mike/CLionProjects/mikecraft/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mikecraft.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mikecraft.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mikecraft.dir/flags.make

CMakeFiles/mikecraft.dir/main.cpp.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mikecraft.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mikecraft.dir/main.cpp.o -c /home/mike/CLionProjects/mikecraft/main.cpp

CMakeFiles/mikecraft.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mikecraft.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mike/CLionProjects/mikecraft/main.cpp > CMakeFiles/mikecraft.dir/main.cpp.i

CMakeFiles/mikecraft.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mikecraft.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mike/CLionProjects/mikecraft/main.cpp -o CMakeFiles/mikecraft.dir/main.cpp.s

CMakeFiles/mikecraft.dir/glad.c.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/glad.c.o: ../glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mikecraft.dir/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mikecraft.dir/glad.c.o   -c /home/mike/CLionProjects/mikecraft/glad.c

CMakeFiles/mikecraft.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mikecraft.dir/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mike/CLionProjects/mikecraft/glad.c > CMakeFiles/mikecraft.dir/glad.c.i

CMakeFiles/mikecraft.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mikecraft.dir/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mike/CLionProjects/mikecraft/glad.c -o CMakeFiles/mikecraft.dir/glad.c.s

CMakeFiles/mikecraft.dir/Shader.cpp.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/Shader.cpp.o: ../Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mikecraft.dir/Shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mikecraft.dir/Shader.cpp.o -c /home/mike/CLionProjects/mikecraft/Shader.cpp

CMakeFiles/mikecraft.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mikecraft.dir/Shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mike/CLionProjects/mikecraft/Shader.cpp > CMakeFiles/mikecraft.dir/Shader.cpp.i

CMakeFiles/mikecraft.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mikecraft.dir/Shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mike/CLionProjects/mikecraft/Shader.cpp -o CMakeFiles/mikecraft.dir/Shader.cpp.s

CMakeFiles/mikecraft.dir/Cube.cpp.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/Cube.cpp.o: ../Cube.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mikecraft.dir/Cube.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mikecraft.dir/Cube.cpp.o -c /home/mike/CLionProjects/mikecraft/Cube.cpp

CMakeFiles/mikecraft.dir/Cube.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mikecraft.dir/Cube.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mike/CLionProjects/mikecraft/Cube.cpp > CMakeFiles/mikecraft.dir/Cube.cpp.i

CMakeFiles/mikecraft.dir/Cube.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mikecraft.dir/Cube.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mike/CLionProjects/mikecraft/Cube.cpp -o CMakeFiles/mikecraft.dir/Cube.cpp.s

CMakeFiles/mikecraft.dir/ChunkManager.cpp.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/ChunkManager.cpp.o: ../ChunkManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mikecraft.dir/ChunkManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mikecraft.dir/ChunkManager.cpp.o -c /home/mike/CLionProjects/mikecraft/ChunkManager.cpp

CMakeFiles/mikecraft.dir/ChunkManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mikecraft.dir/ChunkManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mike/CLionProjects/mikecraft/ChunkManager.cpp > CMakeFiles/mikecraft.dir/ChunkManager.cpp.i

CMakeFiles/mikecraft.dir/ChunkManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mikecraft.dir/ChunkManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mike/CLionProjects/mikecraft/ChunkManager.cpp -o CMakeFiles/mikecraft.dir/ChunkManager.cpp.s

CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.o: ../dep/SimplexNoise.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.o -c /home/mike/CLionProjects/mikecraft/dep/SimplexNoise.cpp

CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mike/CLionProjects/mikecraft/dep/SimplexNoise.cpp > CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.i

CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mike/CLionProjects/mikecraft/dep/SimplexNoise.cpp -o CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.s

CMakeFiles/mikecraft.dir/Chunk.cpp.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/Chunk.cpp.o: ../Chunk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mikecraft.dir/Chunk.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mikecraft.dir/Chunk.cpp.o -c /home/mike/CLionProjects/mikecraft/Chunk.cpp

CMakeFiles/mikecraft.dir/Chunk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mikecraft.dir/Chunk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mike/CLionProjects/mikecraft/Chunk.cpp > CMakeFiles/mikecraft.dir/Chunk.cpp.i

CMakeFiles/mikecraft.dir/Chunk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mikecraft.dir/Chunk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mike/CLionProjects/mikecraft/Chunk.cpp -o CMakeFiles/mikecraft.dir/Chunk.cpp.s

CMakeFiles/mikecraft.dir/FlyCamera.cpp.o: CMakeFiles/mikecraft.dir/flags.make
CMakeFiles/mikecraft.dir/FlyCamera.cpp.o: ../FlyCamera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mikecraft.dir/FlyCamera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mikecraft.dir/FlyCamera.cpp.o -c /home/mike/CLionProjects/mikecraft/FlyCamera.cpp

CMakeFiles/mikecraft.dir/FlyCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mikecraft.dir/FlyCamera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mike/CLionProjects/mikecraft/FlyCamera.cpp > CMakeFiles/mikecraft.dir/FlyCamera.cpp.i

CMakeFiles/mikecraft.dir/FlyCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mikecraft.dir/FlyCamera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mike/CLionProjects/mikecraft/FlyCamera.cpp -o CMakeFiles/mikecraft.dir/FlyCamera.cpp.s

# Object files for target mikecraft
mikecraft_OBJECTS = \
"CMakeFiles/mikecraft.dir/main.cpp.o" \
"CMakeFiles/mikecraft.dir/glad.c.o" \
"CMakeFiles/mikecraft.dir/Shader.cpp.o" \
"CMakeFiles/mikecraft.dir/Cube.cpp.o" \
"CMakeFiles/mikecraft.dir/ChunkManager.cpp.o" \
"CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.o" \
"CMakeFiles/mikecraft.dir/Chunk.cpp.o" \
"CMakeFiles/mikecraft.dir/FlyCamera.cpp.o"

# External object files for target mikecraft
mikecraft_EXTERNAL_OBJECTS =

mikecraft: CMakeFiles/mikecraft.dir/main.cpp.o
mikecraft: CMakeFiles/mikecraft.dir/glad.c.o
mikecraft: CMakeFiles/mikecraft.dir/Shader.cpp.o
mikecraft: CMakeFiles/mikecraft.dir/Cube.cpp.o
mikecraft: CMakeFiles/mikecraft.dir/ChunkManager.cpp.o
mikecraft: CMakeFiles/mikecraft.dir/dep/SimplexNoise.cpp.o
mikecraft: CMakeFiles/mikecraft.dir/Chunk.cpp.o
mikecraft: CMakeFiles/mikecraft.dir/FlyCamera.cpp.o
mikecraft: CMakeFiles/mikecraft.dir/build.make
mikecraft: includes/glfw-3.3/src/libglfw3.a
mikecraft: /usr/lib/x86_64-linux-gnu/librt.so
mikecraft: /usr/lib/x86_64-linux-gnu/libm.so
mikecraft: /usr/lib/x86_64-linux-gnu/libX11.so
mikecraft: CMakeFiles/mikecraft.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable mikecraft"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mikecraft.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mikecraft.dir/build: mikecraft

.PHONY : CMakeFiles/mikecraft.dir/build

CMakeFiles/mikecraft.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mikecraft.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mikecraft.dir/clean

CMakeFiles/mikecraft.dir/depend:
	cd /home/mike/CLionProjects/mikecraft/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mike/CLionProjects/mikecraft /home/mike/CLionProjects/mikecraft /home/mike/CLionProjects/mikecraft/cmake-build-debug /home/mike/CLionProjects/mikecraft/cmake-build-debug /home/mike/CLionProjects/mikecraft/cmake-build-debug/CMakeFiles/mikecraft.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mikecraft.dir/depend


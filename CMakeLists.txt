cmake_minimum_required(VERSION 3.15)
project(mikecraft)

set(CMAKE_CXX_STANDARD 14)

add_executable(mikecraft
                main.cpp glad.c Shader.cpp
                Shader.h Cube.cpp Cube.h
                ChunkManager.cpp ChunkManager.h
                dep/SimplexNoise.cpp dep/SimplexNoise.h
                Chunk.cpp Chunk.h
        FlyCamera.cpp FlyCamera.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(includes/glew-2.1.0/build/cmake)
add_subdirectory(includes/glfw-3.3)

target_link_libraries(mikecraft glfw assimp)




cmake_minimum_required(VERSION 3.16)
project(VoxelEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(VoxelEngine
    external/glad/src/glad.c
    src/main.cpp
    src/core/Window.cpp
)

target_include_directories(VoxelEngine PRIVATE
    external/glad/include
    src
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(VoxelEngine PRIVATE
    OpenGL::GL
    glfw
    glm::glm
)
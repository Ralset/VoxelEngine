cmake_minimum_required(VERSION 3.16)
project(VoxelEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(VoxelEngine
    external/glad/src/glad.c
    src/main.cpp
    src/core/Window.cpp
    src/graphics/Renderer.cpp
    src/core/Input.cpp
    src/core/Application.cpp
    src/graphics/VertexBuffer.cpp
    src/graphics/IndexBuffer.cpp
)

target_include_directories(VoxelEngine PRIVATE
    external/glad/include
    src
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(VoxelEngine
    OpenGL::GL
    glfw
)
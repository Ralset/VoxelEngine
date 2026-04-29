cmake_minimum_required(VERSION 3.16)
project(VoxelEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# --- GLAD as its own library, with relaxed warnings ---
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)
if(NOT MSVC)
    target_compile_options(glad PRIVATE -w)  # silence pedantic warnings in third-party C
endif()

# --- Main executable ---
add_executable(VoxelEngine
    src/main.cpp
    src/core/Window.cpp
)

target_include_directories(VoxelEngine PRIVATE src)

if(MSVC)
    target_compile_options(VoxelEngine PRIVATE /W4)
else()
    target_compile_options(VoxelEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --- Dependencies ---
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
# Note: not using find_package(glfw3) — linking the static archive directly below

target_link_libraries(VoxelEngine PRIVATE
    glad
    OpenGL::GL
    glm::glm
)

# --- Static GLFW + Windows system libs (MinGW/UCRT only) ---
if(WIN32 AND MINGW)
    # Derive the lib path from the compiler location: <root>/bin/g++.exe -> <root>/lib
    get_filename_component(COMPILER_BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    get_filename_component(MSYS_ROOT ${COMPILER_BIN_DIR} DIRECTORY)
    set(GLFW_STATIC_LIB "${MSYS_ROOT}/lib/libglfw3.a")

    if(NOT EXISTS ${GLFW_STATIC_LIB})
        message(FATAL_ERROR "Static GLFW library not found at: ${GLFW_STATIC_LIB}")
    endif()

    message(STATUS "Linking GLFW statically: ${GLFW_STATIC_LIB}")

    target_link_libraries(VoxelEngine PRIVATE
        ${GLFW_STATIC_LIB}
        gdi32
        user32
        shell32
    )

    # Static-link the C++ runtime (libgcc, libstdc++, libwinpthread)
    target_link_options(VoxelEngine PRIVATE
        -static-libgcc
        -static-libstdc++
        -static
    )
endif()

# --- Asset copying ---
add_custom_command(TARGET VoxelEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:VoxelEngine>/assets
)
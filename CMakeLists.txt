cmake_minimum_required(VERSION 3.18)
project(cub3d)

set(CMAKE_C_STANDARD 99)

# Find required packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add libft
add_subdirectory(libs/libft)

# Add MLX42
set(MLX42_BUILD_TESTS OFF CACHE BOOL "")
set(MLX42_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(libs/MLX42)

# Include directories
include_directories(include)
include_directories(libs/libft/include)
include_directories(libs/MLX42/include)

# Source files
file(GLOB SOURCES "src/*.c")

# Create executable
add_executable(cub3d ${SOURCES})

# Link libraries
target_link_libraries(cub3d 
    ft
    mlx42
    glfw
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler flags
target_compile_options(cub3d PRIVATE -Wall -Wextra -Werror)

# Debug-specific flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(cub3d PRIVATE -g -O0)
endif()

# Release-specific flags  
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(cub3d PRIVATE -O2 -DNDEBUG)
endif()

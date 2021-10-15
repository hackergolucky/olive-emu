# Cmake >= 3.19
cmake_minimum_required(VERSION 3.19)
# Project name Olive
project(olive VERSION 0.1)

# Create a variable that holds all our sources
file(GLOB_RECURSE OLIVE_SRCS "source/*.c" "source/*.cpp")
# Header dirs
include_directories(
    ${CMAKE_SOURCE_DIR}/include/
)

# Create executable
add_executable(olive ${OLIVE_SRCS})

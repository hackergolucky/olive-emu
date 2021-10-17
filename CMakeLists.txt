# Cmake >= 3.19
cmake_minimum_required(VERSION 3.19)
# Project name Olive
project(olive VERSION 0.1)

find_package(SDL2 2.0.17 EXACT REQUIRED)
message("Found SDL include dirs at: " ${SDL2_INCLUDE_DIRS})

# Create a variable that holds all our sources
file(GLOB_RECURSE OLIVE_SRCS "source/*.c" "source/*.cpp")
# Header dirs
include_directories(
    ${SDL2_INCLUDE_DIRS}

    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/include/imgui/
)

# Create executable
add_executable(olive ${OLIVE_SRCS})

target_link_libraries(olive
    ${SDL2_LIBRARIES}
)

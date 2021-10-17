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

    ${CMAKE_SOURCE_DIR}/externals/nfde/src/include/

    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/include/imgui/
)

add_subdirectory( ${CMAKE_SOURCE_DIR}/externals/nfde/ )

# Create executable
add_executable(olive ${OLIVE_SRCS})

# If we are on macOS, include the AppKit framework
if (APPLE)

    message("macOS detected! Looking for AppKit!")

    find_library(MACOS_APPKIT AppKit)
    if (NOT MACOS_APPKIT)
        message(FATAL_ERROR "AppKit not found!")
    endif ()

    target_link_libraries(olive
        ${MACOS_APPKIT}
    )

endif ()

target_link_libraries(olive
    ${SDL2_LIBRARIES}
    nfd
)

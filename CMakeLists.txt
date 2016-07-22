cmake_minimum_required(VERSION 2.6)

project(Vox)

set(VOX_VERSION_MAJOR 1)
set(VOX_VERSION_MINOR 0)

include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(source)
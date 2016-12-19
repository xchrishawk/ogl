#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

cmake_minimum_required(VERSION 3.4)
project(ogl)

# CMake packages
find_package(PkgConfig)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Toolchain configuration
set(CMAKE_CXX_FLAGS		"-std=gnu++11")
set(CMAKE_CXX_FLAGS_DEBUG	"-g -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE	"-O3 -s -Wall -Wpedantic")

# -- Subdirectories --

add_subdirectory(doc)
add_subdirectory(src)

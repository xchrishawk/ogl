#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Setup --

# Initial definitions
cmake_minimum_required(VERSION 3.4)
project(ogl)

# CMake libraries
find_package(PkgConfig)

# -- Common Variables --

# Project names
set(APP_EXECUTABLE_NAME 	${CMAKE_PROJECT_NAME})
set(GLFWWRAPPER_LIBRARY_NAME	glfwwrapper)
set(UTIL_LIBRARY_NAME		util)

# Toolchain configuration
set(CMAKE_CXX_FLAGS		"-std=gnu++11")
set(CMAKE_CXX_FLAGS_DEBUG	"-g -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE	"-O3 -s -Wall -Wpedantic")

# Build-specific configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DOGL_DEBUG)
endif()

# Platform-specific configuration
if(UNIX AND NOT APPLE)
  add_definitions(-DOGL_LINUX)
elseif(APPLE)
  add_definitions(-DOGL_MACOS)
else()
  message(FATAL_ERROR "Unrecognized or unsupported platform!")
endif()

# Common libraries
pkg_check_modules(GLFW REQUIRED glfw3)

# Include root directory so we can use qualified paths
include_directories(${CMAKE_SOURCE_DIR})

# -- Subdirectories --

add_subdirectory(app)
add_subdirectory(doc)
add_subdirectory(glfw)
add_subdirectory(util)

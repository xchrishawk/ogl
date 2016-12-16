#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

cmake_minimum_required(VERSION 3.4)
project(ogl)

# Project names
set(APP_EXECUTABLE_NAME 	${CMAKE_PROJECT_NAME})
set(OPENGL_LIBRARY_NAME		opengl)
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

# Include root directory so we can use qualified paths
include_directories(${CMAKE_SOURCE_DIR})

# Subdirectories
add_subdirectory(app)
add_subdirectory(opengl)
add_subdirectory(util)

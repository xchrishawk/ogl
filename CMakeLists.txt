#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

cmake_minimum_required(VERSION 3.4)

# -- Project Configuration --

# Project name
project(ogl)

# CMake packages
find_package(PkgConfig)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Disable in-source builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# -- Subdirectories --

add_subdirectory(doc)
add_subdirectory(src)

# -- Custom Targets --

# Run main application
add_custom_target(run
  ${OGL_EXECUTABLE_NAME}
  DEPENDS ${OGL_EXECUTABLE_NAME}
  COMMENT "Running application...")

# Run unit tests
add_custom_target(runtests
  ${TESTS_EXECUTABLE_NAME}
  DEPENDS ${TESTS_EXECUTABLE_NAME}
  COMMENT "Running tests...")

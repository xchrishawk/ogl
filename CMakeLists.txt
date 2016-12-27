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

# -- Platform-Specific Configuration --

if (UNIX AND NOT APPLE)

  # Define macro for Linux
  add_definitions(-DOGL_LINUX)

elseif (APPLE)

  # Define macro for MacOS
  add_definitions(-DOGL_MACOS)

else()

  # Unknown platform, can't continue
  message(FATAL_ERROR "Unrecognized or unsupported platform!")

endif()

# -- Build Type-Specific Configuration --

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

  # Define debug macro
  add_definitions(-DOGL_DEBUG)

elseif (CMAKE_BUILD_TYPE STREQUAL "Release")

  # Define release macro
  add_definitions(-DOGL_RELEASE)

endif()

# -- Toolchain-Specific Configuration --

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

  # Define macro for GCC
  add_definitions(-DOGL_GCC)

  # Configure toolchain
  set(CMAKE_CXX_FLAGS		"-std=gnu++1z -Wall -Wpedantic")
  set(CMAKE_CXX_FLAGS_DEBUG	"-g")
  set(CMAKE_CXX_FLAGS_RELEASE	"-O3 -s -Wall -Wpedantic -Werror")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")

  # Define macro for clang
  add_definitions(-DOGL_CLANG)

  # Configure toolchain
  set(CMAKE_CXX_FLAGS		"-std=gnu++1z -Wall -Wpedantic")
  set(CMAKE_CXX_FLAGS_DEBUG	"-g")
  set(CMAKE_CXX_FLAGS_RELEASE	"-O3 -Wall -Wpedantic -Werror")

else()

  # Unknown compiler version
  message(FATAL_ERROR "Unknown C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")

endif()

# -- Subdirectories --

add_subdirectory(doc)
add_subdirectory(src)

# -- Run Target --

# Custom target to run the app
add_custom_target(run
  ${APP_EXECUTABLE_NAME}
  DEPENDS ${APP_EXECUTABLE_NAME}
  COMMENT "Running application...")

# -- Test Target --

# Custom target to run tests
add_custom_target(runtests
  ${TEST_EXECUTABLE_NAME}
  DEPENDS ${TEST_EXECUTABLE_NAME}
  COMMENT "Running tests...")

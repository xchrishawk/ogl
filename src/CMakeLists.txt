#
# src/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Common Configuration --

# Allow using include paths relative to src/ directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# -- Build Type-Specific Configuration --

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

  # Build type macro
  add_definitions(-DOGL_DEBUG)

elseif (CMAKE_BUILD_TYPE STREQUAL "Release")

  # Build type macro and disable asserts
  add_definitions(-DOGL_RELEASE)
  add_definitions(-DOGL_NOASSERT)

else()

  # Unknown build type
  message(FATAL_ERROR "Unrecognized or unsupported build type: ${CMAKE_BUILD_TYPE}!")

endif()

# -- Platform-Specific Configuration --

if (UNIX AND NOT APPLE)

  # Platform macro
  add_definitions(-DOGL_LINUX)

elseif (APPLE)

  # Platform macro
  add_definitions(-DOGL_MACOS)

  # Must include /usr/local/include manually
  include_directories(/usr/local/include)

else()

  # Unknown platform
  message(FATAL_ERROR "Unrecognized or unsupported platform!")

endif()

# -- Toolchain-Specific Configuration --

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

  # Compiler macro
  add_definitions(-DOGL_GCC)

  # Configure toolchain
  set(CMAKE_CXX_FLAGS		"-std=gnu++1z -Wall -Wpedantic")
  set(CMAKE_CXX_FLAGS_DEBUG	"-g")
  set(CMAKE_CXX_FLAGS_RELEASE	"-O3 -s -Wall -Wpedantic -Werror")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")

  # Compiler macro
  add_definitions(-DOGL_CLANG)

  # Configure toolchain
  set(CMAKE_CXX_FLAGS		"-std=gnu++1z -Wall -Wpedantic")
  set(CMAKE_CXX_FLAGS_DEBUG	"-g")
  set(CMAKE_CXX_FLAGS_RELEASE	"-O3 -Wall -Wpedantic -Werror")

else()

  # Unknown compiler version
  message(FATAL_ERROR "Unrecognized or unsupported toolchain: ${CMAKE_CXX_COMPILER_ID}!")

endif()

# -- Executables --

add_subdirectory(ogl)
add_subdirectory(tests)

# -- Exports --

set(OGL_EXECUTABLE_NAME ${OGL_EXECUTABLE_NAME} PARENT_SCOPE)
set(TESTS_EXECUTABLE_NAME ${TESTS_EXECUTABLE_NAME} PARENT_SCOPE)

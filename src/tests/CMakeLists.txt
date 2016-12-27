#
# src/tests/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

set(TESTS_EXECUTABLE_NAME tests)
set(TESTS_EXECUTABLE_SOURCES
  main.cpp)

# -- Target Definition --

add_executable(${TESTS_EXECUTABLE_NAME}
  ${TESTS_EXECUTABLE_SOURCES})

# -- Exports --

set(TESTS_EXECUTABLE_NAME ${TESTS_EXECUTABLE_NAME} PARENT_SCOPE)

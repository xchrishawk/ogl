#
# src/tests/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Project name
set(TESTS_EXECUTABLE_NAME tests)

# Project macro
string(TOUPPER ${TESTS_EXECUTABLE_NAME} TESTS_EXECUTABLE_NAME_UPPER)
list(APPEND TESTS_EXECUTABLE_COMPILE_DEFINITIONS -DOGL_${TESTS_EXECUTABLE_NAME_UPPER})

# Source files
set(TESTS_EXECUTABLE_SOURCES
  main.cpp
  app/application_tests.cpp
  glfw/window_manager_tests.cpp)

# Libraries
set(TESTS_EXECUTABLE_LINK_LIBRARIES
  ${APP_LIBRARY_NAME}
  ${GLFW_LIBRARY_NAME}
  ${UTIL_LIBRARY_NAME})

# -- Google Test --

# Make sure we can find Google Test, otherwise bail out
find_package(GTest)
if (NOT ${GTEST_FOUND})
  message(WARNING "Google Test not found! Unit tests will not be built.")
  return()
endif()

# Add additional stuff required by Google Test
list(APPEND TESTS_EXECUTABLE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
list(APPEND TESTS_EXECUTABLE_LINK_LIBRARIES ${GTEST_LIBRARIES})
list(APPEND TESTS_EXECUTABLE_LINK_LIBRARIES pthread)

# -- Target Definition --

add_executable(${TESTS_EXECUTABLE_NAME}
  ${TESTS_EXECUTABLE_SOURCES})
target_compile_definitions(${TESTS_EXECUTABLE_NAME}
  PRIVATE ${TESTS_EXECUTABLE_COMPILE_DEFINITIONS})
target_include_directories(${TESTS_EXECUTABLE_NAME}
  PRIVATE ${TESTS_EXECUTABLE_INCLUDE_DIRECTORIES})
target_link_libraries(${TESTS_EXECUTABLE_NAME}
  ${TESTS_EXECUTABLE_LINK_LIBRARIES})

# -- Exports --

set(TESTS_EXECUTABLE_NAME ${TESTS_EXECUTABLE_NAME} PARENT_SCOPE)

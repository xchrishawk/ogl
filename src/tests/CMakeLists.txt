#
# src/tests/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Executable name
set(TEST_EXECUTABLE_NAME test${CMAKE_PROJECT_NAME})

# Executable source code
set(TEST_EXECUTABLE_SOURCES
  main.cpp)

# Initial configuration
list(APPEND TEST_EXECUTABLE_COMPILE_DEFINITIONS -DOGL_TEST)
list(APPEND TEST_EXECUTABLE_LINK_LIBRARIES ${APP_EXECUTABLE_LINK_LIBRARIES})

# -- Libraries --

# Make sure we can find Google Test, otherwise bail out
find_package(GTest)
if (NOT ${GTEST_FOUND})
  message(WARNING "Google Test not found! Unit tests will not be built.")
  return()
endif()

# Add additional stuff required by Google Test
list(APPEND TEST_EXECUTABLE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
list(APPEND TEST_EXECUTABLE_LINK_LIBRARIES ${GTEST_LIBRARIES})
list(APPEND TEST_EXECUTABLE_LINK_LIBRARIES pthread)

# -- Target Definition --

add_executable(${TEST_EXECUTABLE_NAME}
  ${TEST_EXECUTABLE_SOURCES})
target_compile_definitions(${TEST_EXECUTABLE_NAME}
  PRIVATE ${TEST_EXECUTABLE_COMPILE_DEFINITIONS})
target_include_directories(${TEST_EXECUTABLE_NAME}
  PRIVATE ${TEST_EXECUTABLE_INCLUDE_DIRECTORIES})
target_link_libraries(${TEST_EXECUTABLE_NAME}
  ${TEST_EXECUTABLE_LINK_LIBRARIES})

# -- Exports --

# Executable name
set(TEST_EXECUTABLE_NAME ${TEST_EXECUTABLE_NAME} PARENT_SCOPE)

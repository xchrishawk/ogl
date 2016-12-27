#
# src/tests/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Executable name
set(TEST_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME}_tests)

# Executable source code
set(TEST_EXECUTABLE_SOURCES
  main.cpp)

# Initial configuration
list(APPEND TEST_EXECUTABLE_COMPILE_DEFINITIONS -DOGL_TEST)
list(APPEND TEST_EXECUTABLE_LINK_LIBRARIES ${APP_EXECUTABLE_LINK_LIBRARIES})

# -- Target Definition --

add_executable(${TEST_EXECUTABLE_NAME}
  ${TEST_EXECUTABLE_SOURCES})
target_compile_definitions(${TEST_EXECUTABLE_NAME}
  PRIVATE ${TEST_EXECUTABLE_COMPILE_DEFINITIONS})
target_link_libraries(${TEST_EXECUTABLE_NAME}
  ${TEST_EXECUTABLE_LINK_LIBRARIES})

# -- Exports --

# Executable name
set(TEST_EXECUTABLE_NAME ${TEST_EXECUTABLE_NAME} PARENT_SCOPE)

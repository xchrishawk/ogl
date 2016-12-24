#
# src/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Common Configuration --

# Executable name
set(APP_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})

# Executable source code
set(APP_EXECUTABLE_SOURCES
  main.cpp)

# -- Target Definition --

add_executable(${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_SOURCES})

# -- Run Target --

# Custom target to run the app
add_custom_target(run
  ${APP_EXECUTABLE_NAME}
  DEPENDS ${APP_EXECUTABLE_NAME}
  COMMENT "Running application...")

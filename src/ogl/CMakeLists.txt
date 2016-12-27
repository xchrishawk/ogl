#
# src/ogl/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

set(OGL_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
set(OGL_EXECUTABLE_SOURCES
  main.cpp)

# -- Target Definition --

add_executable(${OGL_EXECUTABLE_NAME}
  ${OGL_EXECUTABLE_SOURCES})

# -- Exports --

set(OGL_EXECUTABLE_NAME ${OGL_EXECUTABLE_NAME} PARENT_SCOPE)

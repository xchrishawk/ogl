#
# src/ogl/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Project name
set(OGL_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})

# Project macro
string(TOUPPER ${OGL_EXECUTABLE_NAME} OGL_EXECUTABLE_NAME_UPPER)
list(APPEND OGL_EXECUTABLE_COMPILE_DEFINITIONS -DOGL_${OGL_EXECUTABLE_NAME_UPPER})

# Source files
set(OGL_EXECUTABLE_SOURCES
  main.cpp)

# Libraries
set(OGL_EXECUTABLE_LINK_LIBRARIES
  ${UTIL_LIBRARY_NAME})

# -- Target Definition --

add_executable(${OGL_EXECUTABLE_NAME}
  ${OGL_EXECUTABLE_SOURCES})
target_compile_definitions(${OGL_EXECUTABLE_NAME}
  PRIVATE ${OGL_EXECUTABLE_COMPILE_DEFINITIONS})
target_link_libraries(${OGL_EXECUTABLE_NAME}
  ${OGL_EXECUTABLE_LINK_LIBRARIES})

# -- Exports --

set(OGL_EXECUTABLE_NAME ${OGL_EXECUTABLE_NAME} PARENT_SCOPE)

#
# src/glfw/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Project name
set(GLFW_LIBRARY_NAME oglglfw)

# Project macro
string(TOUPPER ${GLFW_LIBRARY_NAME} GLFW_LIBRARY_NAME_UPPER)
list(APPEND GLFW_LIBRARY_COMPILE_DEFINITIONS -DOGL_${GLFW_LIVRARY_NAME_UPPER})

# Source files
set(GLFW_LIBRARY_SOURCES
  window_manager.cpp)

# -- Target Definition --

add_library(${GLFW_LIBRARY_NAME} STATIC
  ${GLFW_LIBRARY_SOURCES})
target_compile_definitions(${GLFW_LIBRARY_NAME}
  PRIVATE ${GLFW_LIBRARY_COMPILE_DEFINITIONS})

# -- Exports --

set(GLFW_LIBRARY_NAME ${GLFW_LIBRARY_NAME} PARENT_SCOPE)

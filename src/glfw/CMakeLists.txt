#
# glfw/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Inputs --

set(LIBGLFW_LIBRARY_SOURCES
  glfw.cpp)

# -- Target Definition --

add_library(
  ${LIBGLFW_LIBRARY_NAME} STATIC
  ${LIBGLFW_LIBRARY_SOURCES})

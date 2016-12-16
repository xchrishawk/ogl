#
# opengl/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Inputs --

set(LIBOPENGL_LIBRARY_SOURCES
  opengl.cpp)

# -- Target Definition --

add_library(
  ${LIBOPENGL_LIBRARY_NAME} STATIC
  ${LIBOPENGL_LIBRARY_SOURCES})

#
# opengl/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# Source files
set(OPENGL_LIBRARY_SOURCES
  opengl.cpp)

# Library configuration
add_library(
  ${OPENGL_LIBRARY_NAME} STATIC
  ${OPENGL_LIBRARY_SOURCES})

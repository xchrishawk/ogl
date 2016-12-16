#
# opengl/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Inputs --

list(APPEND LIBOPENGL_LIBRARY_SOURCES
  opengl.cpp
  glfw/glfw.cpp
  glfw/window.cpp)

if(UNIX AND NOT APPLE)

  # Linux-specific sources
  list(APPEND LIBOPENGL_LIBRARY_SOURCES
    linux/glew.cpp
    linux/opengl_linux.cpp)

else()

  # Unknown platform?
  message(FATAL_ERROR "Unrecognized or unsupported platform!")

endif()

# -- Target Definition --

add_library(
  ${LIBOPENGL_LIBRARY_NAME} STATIC
  ${LIBOPENGL_LIBRARY_SOURCES})

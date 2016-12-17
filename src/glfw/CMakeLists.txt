#
# glfw/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Inputs --

set(GLFWWRAPPER_LIBRARY_SOURCES
  glfw.cpp
  window.cpp)

list(APPEND GLFW_LIBRARY_INCLUDE_DIRS ${GLFW_INCLUDE_DIRS})
list(APPEND GLFW_LIBRARY_COMPILE_OPTIONS ${GLFW_CFLAGS_OTHER})

# -- Target Definition --

# Static library
add_library(
  ${GLFWWRAPPER_LIBRARY_NAME} STATIC
  ${GLFWWRAPPER_LIBRARY_SOURCES})

# Additional target configuration
target_include_directories(${GLFWWRAPPER_LIBRARY_NAME} PUBLIC ${GLFWWRAPPER_LIBRARY_INCLUDE_DIRS})
target_compile_options(${GLFWWRAPPER_LIBRARY_NAME} PUBLIC ${GLFWWRAPPER_LIBRARY_COMPILE_OPTIONS})

#
# app/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Inputs --

# Source files
set(APP_EXECUTABLE_SOURCES
  application.cpp
  main.cpp)

# Project libraries
list(APPEND APP_EXECUTABLE_LIBRARIES
  ${LIBOPENGL_LIBRARY_NAME}
  ${LIBUTIL_LIBRARY_NAME})

# -- Third Party Libraries --

# Platform-specific setup
if(UNIX AND NOT APPLE)

  # TODO - use GLEW

elseif(APPLE)

  # Use OpenGL.framework
  find_library(OPENGL_FRAMEWORK OpenGL)
  list(APPEND APP_EXECUTABLE_LIBRARIES ${OPENGL_FRAMEWORK})

else()

  # Unknown platform??
  message(FATAL_ERROR "Unrecognized or unsupported platform!")

endif()

# GLFW library is required regardless of platform
pkg_check_modules(GLFW REQUIRED glfw3)
link_directories(${GLFW_LIBRARY_DIRS})
list(APPEND APP_EXECUTABLE_INCLUDE_DIRS ${GLFW_INCLUDE_DIRS})
list(APPEND APP_EXECUTABLE_COMPILE_OPTIONS ${GLFW_CFLAGS_OTHER})
list(APPEND APP_EXECUTABLE_LIBRARIES ${GLFW_LIBRARIES})

# -- Target Definition --

# Executable target
add_executable(
  ${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_SOURCES})

# Additional target configuration
target_include_directories(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_INCLUDE_DIRS})
target_compile_options(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_COMPILE_OPTIONS})
target_link_libraries(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_LIBRARIES})

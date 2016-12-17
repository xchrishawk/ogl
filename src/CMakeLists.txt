#
# src/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Target Configuration --

# Executable name
set(APP_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})

# Executable source code
set(APP_EXECUTABLE_SOURCES
  main.cpp
  app/application.cpp
  app/input.cpp
  app/renderer.cpp
  app/state.cpp
  glfw/glfw.cpp
  glfw/window.cpp
  opengl/error.cpp
  opengl/opengl.cpp
  util/debug.cpp)

# Include src directory so we can use relative paths
list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

# Define OGL_DEBUG if this is a debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_DEBUG)
endif()

# Platform-specific setup
if(UNIX AND NOT APPLE)

  # Define Linux macro
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_LINUX)

  # Include GLEW library
  pkg_check_modules(GLEW REQUIRED glew)
  link_directories(${GLEW_LIBRARY_DIRS})
  list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${GLEW_INCLUDE_DIRS})
  list(APPEND APP_EXECUTABLE_COMPILE_OPTIONS ${GLEW_CFLAGS_OTHER})
  list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${GLEW_LIBRARIES})

elseif(APPLE)

  # Define MacOS macro
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_MACOS)

  # Use OpenGL.framework
  find_package(OpenGL REQUIRED)
  list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${OPENGL_INCLUDE_DIR})
  list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${OPENGL_LIBRARIES})

else()

  # Unknown platform???
  message(FATAL_ERROR "Unrecognized or unsupported platform!")

endif()

# -- Libraries --

# GLFW is required on all platforms
pkg_check_modules(GLFW REQUIRED glfw3)
link_directories(${GLFW_LIBRARY_DIRS})
list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE_DIRS})
list(APPEND APP_EXECUTABLE_COMPILE_OPTIONS ${GLFW_CFLAGS_OTHER})
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${GLFW_LIBRARIES})

# -- Target Definition --

add_executable(${APP_EXECUTABLE_NAME} ${APP_EXECUTABLE_SOURCES})
target_compile_definitions(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_DEFINITIONS})
target_include_directories(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_INCLUDE_DIRECTORIES})
target_compile_options(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_COMPILE_OPTIONS})
target_link_libraries(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_LINK_LIBRARIES})

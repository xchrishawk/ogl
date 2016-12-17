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
  glfw/glfw.cpp
  glfw/window.cpp
  util/debug.cpp)

# Include src directory so we can use relative paths
list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

# Define OGL_DEBUG if this is a debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_DEBUG)
endif()

# Define platform macros
if(UNIX AND NOT APPLE)
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_LINUX)
elseif(APPLE)
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_MACOS)
else()
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

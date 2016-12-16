#
# app/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# Source files
set(APP_EXECUTABLE_SOURCES
  application.cpp
  main.cpp)

# Executable target
add_executable(
  ${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_SOURCES})

# Libraries
target_link_libraries(
  ${APP_EXECUTABLE_NAME}
  ${OPENGL_LIBRARY_NAME}
  ${UTIL_LIBRARY_NAME})

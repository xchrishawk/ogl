#
# src/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Common Configuration --

# Include src/, so we can use paths relative to src/ for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# -- Subdirectories --

add_subdirectory(util)

# -- Project Configuration --

# Executable name
set(APP_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
set(APP_EXECUTABLE_NAME ${APP_EXECUTABLE_NAME} PARENT_SCOPE)

# Executable source code
set(APP_EXECUTABLE_SOURCES
  main.cpp)

# Initial configuration
list(APPEND APP_EXECUTABLE_COMPILE_DEFINITIONS -DOGL_APP)
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${UTIL_LIBRARY_NAME})

# -- Target Definition --

add_executable(${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_SOURCES})
target_compile_definitions(${APP_EXECUTABLE_NAME}
  PRIVATE ${APP_EXECUTABLE_COMPILE_DEFINITIONS})
target_link_libraries(${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_LINK_LIBRARIES})

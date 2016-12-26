#
# src/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Common Configuration --

# Include src/, so we can use paths relative to src/ for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Initialize this variable so subdirectories can add to it as needed
set(APP_EXECUTABLE_LINK_DIRECTORIES "")

# -- Platform-Specific Configuration --

if (APPLE)

  # Must include /usr/local/include manually
  include_directories(/usr/local/include)

endif()

# -- Subdirectories --

add_subdirectory(app)
add_subdirectory(opengl)
add_subdirectory(resources)
add_subdirectory(util)
add_subdirectory(window)

# -- Project Configuration --

# Executable name
set(APP_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})
set(APP_EXECUTABLE_NAME ${APP_EXECUTABLE_NAME} PARENT_SCOPE)

# Executable source code
set(APP_EXECUTABLE_SOURCES
  main.cpp)

# Initial configuration
list(APPEND APP_EXECUTABLE_COMPILE_DEFINITIONS -DOGL_APP)
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${APP_LIBRARY_NAME})
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${OPENGL_LIBRARY_NAME})
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${RESOURCES_LIBRARY_NAME})
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${UTIL_LIBRARY_NAME})
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${WINDOW_LIBRARY_NAME})

message(STATUS ${APP_EXECUTABLE_LINK_DIRECTORIES})
link_directories(${APP_EXECUTABLE_LINK_DIRECTORIES})

# -- Target Definition --

add_executable(${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_SOURCES})
target_compile_definitions(${APP_EXECUTABLE_NAME}
  PRIVATE ${APP_EXECUTABLE_COMPILE_DEFINITIONS})
target_link_libraries(${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_LINK_LIBRARIES})

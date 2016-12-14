cmake_minimum_required(VERSION 3.5)
project(ogl)

# -- Imports --

find_package(PkgConfig)

# -- Inputs --

set(EXECUTABLE_TARGET
  ${CMAKE_PROJECT_NAME})

set(EXECUTABLE_SOURCES
  main.cpp
  app/application.cpp
  app/examples.cpp
  app/input.cpp
  app/mesh.cpp
  app/object.cpp
  app/renderer.cpp
  app/state.cpp
  opengl/buffer.cpp
  opengl/error.cpp
  opengl/glew.cpp
  opengl/glfw.cpp
  opengl/program.cpp
  opengl/shader.cpp
  opengl/texture.cpp
  opengl/vertex_array.cpp
  opengl/window.cpp
  shaders/shader_sources.cpp
  util/debug.cpp
  util/misc.cpp)

set(EXECUTABLE_SHADERS
  default_vertex_shader.glsl
  default_fragment_shader.glsl)

# -- Common Setup --

# Include root of source tree as an include dir so relative paths work
list(APPEND EXECUTABLE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR})

# Compiler configuration
set(CMAKE_CXX_FLAGS_DEBUG "-std=gnu++11 -g -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-std=gnu++11 -s -O3")

# Add GLFW library
pkg_check_modules(GLFW REQUIRED glfw3)
list(APPEND EXECUTABLE_INCLUDE_DIRS ${GLFW_INCLUDE_DIRS})
list(APPEND EXECUTABLE_CFLAGS ${GLFW_CFLAGS_OTHER})
list(APPEND EXECUTABLE_LIBRARIES ${GLFW_LIBRARIES})

# -- Platform-Specific Setup --

if(UNIX AND NOT APPLE)

  # Define Linux platform
  list(APPEND EXECUTABLE_DEFINITIONS OGL_PLATFORM=LINUX)

  # Add GLEW library
  pkg_check_modules(GLEW REQUIRED glew)
  list(APPEND EXECUTABLE_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
  list(APPEND EXECUTABLE_CFLAGS ${GLEW_CFLAGS_OTHER})
  list(APPEND EXECUTABLE_LIBRARIES ${GLEW_LIBRARIES})

elseif(APPLE)

  # Define MacOS platform
  list(APPEND EXECUTABLE_DEFINITIONS OGL_PLATFORM=MACOS)

else()

  # Unknown platform??
  message(FATAL_ERROR "Unknown platform")

endif()

# -- Pre-Process Shader Code --

foreach(SHADER ${EXECUTABLE_SHADERS})
  set(SHADER_INPUT_PATH "${CMAKE_SOURCE_DIR}/shaders/${SHADER}")
  set(SHADER_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/gen/${SHADER}.inc")
  list(APPEND EXECUTABLE_PROCESSED_SHADERS ${SHADER_OUTPUT_PATH})
  add_custom_command(
    DEPENDS ${SHADER_INPUT_PATH}
    OUTPUT ${SHADER_OUTPUT_PATH}
    COMMAND cat ${SHADER_INPUT_PATH} | xxd -i > ${SHADER_OUTPUT_PATH}
    COMMENT "Processing ${SHADER}")
endforeach()

# -- Main Executable --

add_executable(
  ${EXECUTABLE_TARGET}
  ${EXECUTABLE_SOURCES}
  ${EXECUTABLE_PROCESSED_SHADERS})

target_compile_definitions(
  ${EXECUTABLE_TARGET}
  PUBLIC ${EXECUTABLE_DEFINITIONS})

target_include_directories(
  ${EXECUTABLE_TARGET}
  PUBLIC ${EXECUTABLE_INCLUDE_DIRS})

target_compile_options(
  ${EXECUTABLE_TARGET}
  PUBLIC ${EXECUTABLE_CFLAGS})

target_link_libraries(
  ${EXECUTABLE_TARGET}
  PUBLIC ${EXECUTABLE_LIBRARIES})

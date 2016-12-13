cmake_minimum_required(VERSION 3.5)
project(ogl)

# -- Package Setup --

find_package(PkgConfig)

pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

# -- Pre-Process Shader Code --

set(GLSL_SOURCES
  default_vertex_shader.glsl
  default_fragment_shader.glsl)

foreach(GLSL ${GLSL_SOURCES})
  set(GLSL_INPUT_PATH ${CMAKE_SOURCE_DIR}/shaders/${GLSL})
  set(GLSL_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/gen/${GLSL}.inc)
  list(APPEND PROCESSED_GLSL_SOURCES ${GLSL_OUTPUT_PATH})
  add_custom_command(
    OUTPUT ${GLSL_OUTPUT_PATH}
    COMMAND cat ${GLSL_INPUT_PATH} | xxd -i > ${GLSL_OUTPUT_PATH}
    COMMENT "Processing ${GLSL}")
endforeach()

# -- Main Executable --

set(EXECUTABLE_TARGET ${CMAKE_PROJECT_NAME})

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

add_executable(
  ${EXECUTABLE_TARGET}
  ${EXECUTABLE_SOURCES}
  ${PROCESSED_GLSL_SOURCES})

target_include_directories(
  ${EXECUTABLE_TARGET}
  PUBLIC ${CMAKE_SOURCE_DIR}
  PUBLIC ${GLEW_INCLUDE_DIRS}
  PUBLIC ${GLFW_INCLUDE_DIRS})

target_compile_options(
  ${EXECUTABLE_TARGET}
  PUBLIC -std=gnu++11 -g -Wall -Wpedantic
  PUBLIC ${GLEW_CFLAGS_OTHER}
  PUBLIC ${GLFW_CFLAGS_OTHER})

target_link_libraries(
  ${EXECUTABLE_TARGET}
  PUBLIC ${GLEW_LIBRARIES}
  PUBLIC ${GLFW_LIBRARIES})

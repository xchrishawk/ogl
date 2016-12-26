#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Library name
set(RESOURCES_LIBRARY_NAME oglresources)

# Library source code
set(RESOURCES_LIBRARY_SOURCES
  resources.cpp)

# Initial configuration
string(TOUPPER ${RESOURCES_LIBRARY_NAME} RESOURCES_LIBRARY_NAME_UPPER)
list(APPEND RESOURCES_LIBRARY_COMPILE_DEFINITIONS -DOGL_LIB${RESOURCES_LIBRARY_NAME_UPPER})

# -- Common Configuration --

# Make top-level include directory for resource include files
set(RESOURCES_INCLUDE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)
file(MAKE_DIRECTORY ${RESOURCES_INCLUDE_DIRECTORY})
list(APPEND RESOURCES_LIBRARY_INCLUDE_DIRECTORIES ${RESOURCES_INCLUDE_DIRECTORY})

# -- Shader Processing --

# Make directory for shader include files
set(RESOURCES_SHADERS_INCLUDE_DIRECTORY ${RESOURCES_INCLUDE_DIRECTORY}/shaders)
file(MAKE_DIRECTORY ${RESOURCES_SHADERS_INCLUDE_DIRECTORY})

# List of shaders to process
set(SHADER_INPUT_FILES
  simple_vertex_shader.glsl
  simple_fragment_shader.glsl)

# Pre-process each shader
foreach(SHADER_INPUT_FILE ${SHADER_INPUT_FILES})
  set(SHADER_INPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER_INPUT_FILE})
  set(SHADER_OUTPUT_PATH ${RESOURCES_SHADERS_INCLUDE_DIRECTORY}/${SHADER_INPUT_FILE}.inc)
  list(APPEND RESOURCES_LIBRARY_RESOURCES ${SHADER_OUTPUT_PATH})
  add_custom_command(
    DEPENDS ${SHADER_INPUT_PATH}
    OUTPUT ${SHADER_OUTPUT_PATH}
    COMMAND cat ${SHADER_INPUT_PATH} | xxd -i > ${SHADER_OUTPUT_PATH}
    COMMENT "Processing ${SHADER_INPUT_FILE}")
endforeach()

# -- Target Definition --

add_library(${RESOURCES_LIBRARY_NAME} STATIC
  ${RESOURCES_LIBRARY_SOURCES}
  ${RESOURCES_LIBRARY_RESOURCES})
target_compile_definitions(${RESOURCES_LIBRARY_NAME}
  PRIVATE ${RESOURCES_LIBRARY_COMPILE_DEFINITIONS})
target_include_directories(${RESOURCES_LIBRARY_NAME}
  PRIVATE ${RESOURCES_LIBRARY_INCLUDE_DIRECTORIES})

# -- Exports --

# Library name
set(RESOURCES_LIBRARY_NAME ${RESOURCES_LIBRARY_NAME} PARENT_SCOPE)

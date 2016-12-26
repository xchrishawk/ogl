#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Library name
set(RESOURCES_LIBRARY_NAME oglresources)
set(RESOURCES_LIBRARY_NAME ${RESOURCES_LIBRARY_NAME} PARENT_SCOPE)

# Library source code
set(RESOURCES_LIBRARY_SOURCES
  resource_manager.cpp)

# Initial configuration
string(TOUPPER ${RESOURCES_LIBRARY_NAME} RESOURCES_LIBRARY_NAME_UPPER)
list(APPEND RESOURCES_LIBRARY_COMPILE_DEFINITIONS -DOGL_LIB${RESOURCES_LIBRARY_NAME_UPPER})

# -- Shader Processing --

# List of shaders to process
# set(RESOURCES_LIBRARY_GLSL_SOURCES
#   simple_vertex_shader.glsl
#   simple_fragment_shader.glsl)
#
# # Create directory for shader include files
# set(SHADER_INCLUDE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)
# file(MAKE_DIRECTORY ${SHADER_INCLUDE_DIRECTORY})
# list(APPEND RESOURCES_LIBRARY_INCLUDE_DIRECTORIES ${SHADER_INCLUDE_DIRECTORY})
#
# # Process each shader
# foreach(SHADER ${SHADERS_LIBRARY_GLSL_SOURCES})
#   set(SHADER_OUTPUT_PATH "${SHADER_INCLUDE_DIRECTORY}/${SHADER}.inc")
#   list(APPEND SHADERS_LIBRARY_SOURCES ${SHADER_OUTPUT_PATH})
#   add_custom_command(
#     DEPENDS ${SHADER}
#     OUTPUT ${SHADER_OUTPUT_PATH}
#     COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/${SHADER} | xxd -i > ${SHADER_OUTPUT_PATH}
#     COMMENT "Processing ${SHADER}")
# endforeach()

# -- Target Definition --

add_library(${RESOURCES_LIBRARY_NAME} STATIC
  ${RESOURCES_LIBRARY_SOURCES})
target_compile_definitions(${RESOURCES_LIBRARY_NAME}
  PRIVATE ${RESOURCES_LIBRARY_COMPILE_DEFINITIONS})
target_include_directories(${RESOURCES_LIBRARY_NAME}
  PRIVATE ${RESOURCES_LIBRARY_INCLUDE_DIRECTORIES})

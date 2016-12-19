#
# src/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Common Configuration --

# Executable name
set(APP_EXECUTABLE_NAME ${CMAKE_PROJECT_NAME})

# Executable source code
set(APP_EXECUTABLE_SOURCES
  main.cpp
  app/application.cpp
  app/input.cpp
  app/object_factory.cpp
  app/renderer.cpp
  app/state.cpp
  glfw/glfw.cpp
  glfw/window.cpp
  opengl/buffer.cpp
  opengl/error.cpp
  opengl/opengl.cpp
  opengl/program.cpp
  opengl/shader.cpp
  opengl/vertex_array.cpp
  scene/component.cpp
  scene/mesh.cpp
  scene/object.cpp
  scene/scene.cpp
  shaders/shader_manager.cpp
  util/debug.cpp)

# Executable shader source code
set(APP_EXECUTABLE_SHADERS
  shaders/vertex_shader.glsl
  shaders/fragment_shader.glsl)

# Include src directory so we can use relative paths
list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

# Define OGL_DEBUG if this is a debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_DEBUG)
endif()

# Include GLFW library
pkg_check_modules(GLFW REQUIRED glfw3)
link_directories(${GLFW_LIBRARY_DIRS})
list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE_DIRS})
list(APPEND APP_EXECUTABLE_COMPILE_OPTIONS ${GLFW_CFLAGS_OTHER})
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${GLFW_LIBRARIES})

# Include GLEW library
pkg_check_modules(GLEW REQUIRED glew)
link_directories(${GLEW_LIBRARY_DIRS})
list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${GLEW_INCLUDE_DIRS})
list(APPEND APP_EXECUTABLE_COMPILE_OPTIONS ${GLEW_CFLAGS_OTHER})
list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${GLEW_LIBRARIES})

# -- Platform-Specific Configuration --

if(UNIX AND NOT APPLE)

  # Define Linux macro
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_LINUX)

elseif(APPLE)

  # Define MacOS macro
  list(APPEND APP_EXECUTABLE_DEFINITIONS -DOGL_MACOS)

  # Must link with OpenGL.framework
  find_package(OpenGL REQUIRED)
  list(APPEND APP_EXECUTABLE_LINK_LIBRARIES ${OPENGL_LIBRARIES})

  # Explicitly include /usr/local/include for GLM
  list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES /usr/local/include)

else()

  # Unknown platform???
  message(FATAL_ERROR "Unrecognized or unsupported platform!")

endif()

# -- Shader Processing --

# Create directory for shader include files
set(SHADER_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIRECTORY})
list(APPEND APP_EXECUTABLE_INCLUDE_DIRECTORIES ${SHADER_OUTPUT_DIRECTORY})

# Process each shader
foreach(SHADER ${APP_EXECUTABLE_SHADERS})
  set(SHADER_INPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER}")
  get_filename_component(SHADER_FILE_NAME ${SHADER_INPUT_PATH} NAME)
  set(SHADER_OUTPUT_PATH "${SHADER_OUTPUT_DIRECTORY}/${SHADER_FILE_NAME}.inc")
  list(APPEND APP_EXECUTABLE_PROCESSED_SHADERS ${SHADER_OUTPUT_PATH})
  add_custom_command(
    DEPENDS ${SHADER_INPUT_PATH}
    OUTPUT ${SHADER_OUTPUT_PATH}
    COMMAND cat ${SHADER_INPUT_PATH} | xxd -i > ${SHADER_OUTPUT_PATH}
    COMMENT "Processing ${SHADER}")
endforeach()

# -- Target Definition --

add_executable(${APP_EXECUTABLE_NAME}
  ${APP_EXECUTABLE_SOURCES}
  ${APP_EXECUTABLE_PROCESSED_SHADERS})

target_compile_definitions(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_DEFINITIONS})
target_include_directories(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_INCLUDE_DIRECTORIES})
target_compile_options(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_COMPILE_OPTIONS})
target_link_libraries(${APP_EXECUTABLE_NAME} PUBLIC ${APP_EXECUTABLE_LINK_LIBRARIES})

#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Library name
set(OPENGL_LIBRARY_NAME oglopengl)
set(OPENGL_LIBRARY_NAME ${OPENGL_LIBRARY_NAME} PARENT_SCOPE)

# Library source code
set(OPENGL_LIBRARY_SOURCES
  impl/opengl_interface.cpp
  impl/opengl_shader.cpp)

# Initial configuration
string(TOUPPER ${OPENGL_LIBRARY_NAME} OPENGL_LIBRARY_NAME_UPPER)
list(APPEND OPENGL_LIBRARY_COMPILE_DEFINITIONS -DOGL_LIB${OPENGL_LIBRARY_NAME_UPPER})

# -- Libraries --

# Include GLEW library
pkg_check_modules(GLEW REQUIRED glew)
link_directories(${GLEW_LIBRARY_DIRS})
list(APPEND OPENGL_LIBRARY_INCLUDE_DIRECTORIES ${GLEW_INCLUDE_DIRS})
list(APPEND OPENGL_LIBRARY_COMPILE_OPTIONS ${GLEW_CFLAGS_OTHER})
list(APPEND OPENGL_LIBRARY_LINK_LIBRARIES ${GLEW_LIBRARIES})

# -- Target Definition --

add_library(${OPENGL_LIBRARY_NAME} STATIC
  ${OPENGL_LIBRARY_SOURCES})
target_compile_definitions(${OPENGL_LIBRARY_NAME}
  PRIVATE ${OPENGL_LIBRARY_COMPILE_DEFINITIONS})
target_compile_options(${OPENGL_LIBRARY_NAME}
  PRIVATE ${OPENGL_LIBRARY_COMPILE_OPTIONS})
target_link_libraries(${OPENGL_LIBRARY_NAME}
  PUBLIC ${OPENGL_LIBRARY_LINK_LIBRARIES})

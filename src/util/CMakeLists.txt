#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Library name
set(UTIL_LIBRARY_NAME util)
set(UTIL_LIBRARY_NAME ${UTIL_LIBRARY_NAME} PARENT_SCOPE)

# Library source code
set(UTIL_LIBRARY_SOURCES
  debug.cpp)

# Initial configuration
list(APPEND UTIL_LIBRARY_COMPILE_DEFINITIONS -DOGL_LIBUTIL)

# -- Target Definition --

add_library(${UTIL_LIBRARY_NAME} STATIC
  ${UTIL_LIBRARY_SOURCES})
target_compile_definitions(${UTIL_LIBRARY_NAME}
  PRIVATE ${UTIL_LIBRARY_COMPILE_DEFINITIONS})

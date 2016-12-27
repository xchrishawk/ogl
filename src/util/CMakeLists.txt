#
# src/util/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Project name
set(UTIL_LIBRARY_NAME oglutil)

# Project macro
string(TOUPPER ${UTIL_LIBRARY_NAME} UTIL_LIBRARY_NAME_UPPER)
list(APPEND UTIL_LIBRARY_COMPILE_DEFINITIONS -DOGL_${UTIL_LIBRARY_NAME_UPPER})

# Source files
set(UTIL_LIBRARY_SOURCES
  debug.cpp)

# -- Target Definition --

add_library(${UTIL_LIBRARY_NAME} STATIC
  ${UTIL_LIBRARY_SOURCES})
target_compile_definitions(${UTIL_LIBRARY_NAME}
  PRIVATE ${UTIL_LIBRARY_COMPILE_DEFINITIONS})

# -- Exports --

set(UTIL_LIBRARY_NAME ${UTIL_LIBRARY_NAME} PARENT_SCOPE)

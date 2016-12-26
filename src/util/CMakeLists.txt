#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Library name
set(UTIL_LIBRARY_NAME oglutil)

# Library source code
set(UTIL_LIBRARY_SOURCES
  debug.cpp)

# Initial configuration
string(TOUPPER ${UTIL_LIBRARY_NAME} UTIL_LIBRARY_NAME_UPPER)
list(APPEND UTIL_LIBRARY_COMPILE_DEFINITIONS -DOGL_LIB${UTIL_LIBRARY_NAME_UPPER})

# -- Target Definition --

add_library(${UTIL_LIBRARY_NAME} STATIC
  ${UTIL_LIBRARY_SOURCES})
target_compile_definitions(${UTIL_LIBRARY_NAME}
  PRIVATE ${UTIL_LIBRARY_COMPILE_DEFINITIONS})

# -- Exports --

# Library name
set(UTIL_LIBRARY_NAME ${UTIL_LIBRARY_NAME} PARENT_SCOPE)

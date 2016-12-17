#
# util/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Inputs --

set(UTIL_LIBRARY_SOURCES
  debug.cpp)

# -- Target Definition --

add_library(
  ${UTIL_LIBRARY_NAME} STATIC
  ${UTIL_LIBRARY_SOURCES})

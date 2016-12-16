#
# util/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Inputs --

set(LIBUTIL_LIBRARY_SOURCES
  strings.cpp)

# -- Target Definition --

add_library(
  ${LIBUTIL_LIBRARY_NAME} STATIC
  ${LIBUTIL_LIBRARY_SOURCES})

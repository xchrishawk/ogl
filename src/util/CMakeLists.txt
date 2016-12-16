#
# util/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# Source files
set(UTIL_LIBRARY_SOURCES
  debug.cpp
  random.cpp)

# Library configuration
add_library(
  ${UTIL_LIBRARY_NAME} STATIC
  ${UTIL_LIBRARY_SOURCES})

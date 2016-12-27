#
# src/app/CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Project name
set(APP_LIBRARY_NAME oglapp)

# Project macro
string(TOUPPER ${APP_LIBRARY_NAME} APP_LIBRARY_NAME_UPPER)
list(APPEND APP_LIBRARY_COMPILE_DEFINITIONS -DOGL_${APP_LIBRARY_NAME_UPPER})

# Source files
set(APP_LIBRARY_SOURCES
  application.cpp)

# -- Target Definition --

add_library(${APP_LIBRARY_NAME} STATIC
  ${APP_LIBRARY_SOURCES})
target_compile_definitions(${APP_LIBRARY_NAME}
  PRIVATE ${APP_LIBRARY_COMPILE_DEFINITIONS})

# -- Exports --

set(APP_LIBRARY_NAME ${APP_LIBRARY_NAME} PARENT_SCOPE)

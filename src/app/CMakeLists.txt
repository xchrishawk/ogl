#
# CMakeLists.txt
# Chris Vig (chris@invictus.so)
#

# -- Project Configuration --

# Library name
set(APP_LIBRARY_NAME oglapp)
set(APP_LIBRARY_NAME ${APP_LIBRARY_NAME} PARENT_SCOPE)

# Library source code
set(APP_LIBRARY_SOURCES
  application.cpp
  input_manager.cpp
  state/trivial_state_manager.cpp)

# Initial configuration
string(TOUPPER ${APP_LIBRARY_NAME} APP_LIBRARY_NAME_UPPER)
list(APPEND APP_LIBRARY_COMPILE_DEFINITIONS -DOGL_LIB${APP_LIBRARY_NAME_UPPER})

# -- Target Definition --

add_library(${APP_LIBRARY_NAME} STATIC
  ${APP_LIBRARY_SOURCES})
target_compile_definitions(${APP_LIBRARY_NAME}
  PRIVATE ${APP_LIBRARY_COMPILE_DEFINITIONS})

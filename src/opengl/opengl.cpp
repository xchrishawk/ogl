/**
 * opengl.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <iostream>

#include "opengl/opengl.hpp"
#include "util/debug.hpp"

#if defined(OGL_LINUX)
  #include "opengl/linux/opengl_linux.hpp"
#endif

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

opengl_factory& opengl_factory::platform_default()
{
#if defined(OGL_LINUX)
  static opengl_linux_factory factory;
#endif
  return factory;
}

/**
 * opengl.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_OPENGL_HPP
#define OGL_OPENGL_OPENGL_HPP

/* -- Includes -- */

#if defined(OGL_PLATFORM) && OGL_PLATFORM == LINUX
  #include <GL/glew.h>
#elif defined(OGL_PLATFORM) && OGL_PLATFORM == MACOS
  #include <GL/gl.h>
#else
  #error Platform undefined or unsupported!
#endif

#include <GLFW/glfw3.h>

#endif /* OGL_OPENGL_OPENGL_HPP */

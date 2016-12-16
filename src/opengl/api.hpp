/**
 * api.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#if defined(OGL_LINUX)

  #include <GL/glew.h>
  #include <GLFW/glfw3.h>

#elif defined(OGL_MACOS)

  #include <OpenGL/gl.h>
  #include <GLFW/glfw3.h>

#else

  #error Unrecognized or unsupported platform!

#endif

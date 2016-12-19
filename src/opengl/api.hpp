/**
 * @file	api.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Includes -- */

#if defined(OGL_LINUX)

  // Use GLEW and GLFW on Linux
  #include <GL/glew.h>
  #include <GLFW/glfw3.h>

#elif defined(OGL_MACOS)

  // Use GLEW and GLFW on macOS
  #include <GL/glew.h>
  #include <GLFW/glfw3.h>

#else

  // Unknown platform??
  #error Unrecognized or unsupported platform!

#endif

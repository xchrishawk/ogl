/**
 * error.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_ERROR_HPP
#define OGL_OPENGL_ERROR_HPP

/* -- Includes -- */

#include <string>
#include <GL/glew.h>

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Throws an exception for the previous OpenGL error. */
  void opengl_throw_last_error(const std::string& message)
    __attribute__((noreturn));

  /** Returns the most recent OpenGL error in the queue. */
  GLenum opengl_last_error();

  /** Returns a string for the specified OpenGL error. */
  std::string opengl_error_string(GLenum error);

}

#endif /* OGL_OPENGL_ERROR_HPP */

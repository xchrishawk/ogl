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

  /** Returns the most recent OpenGL error in the queue. */
  GLenum opengl_last_error();

  /** Returns a string for the specified OpenGL error. */
  std::string opengl_error_string(GLenum error);

}

#endif /* OGL_OPENGL_ERROR_HPP */

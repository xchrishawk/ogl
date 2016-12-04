/**
 * opengl.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OPENGL_HPP
#define OPENGL_HPP

/* -- Includes -- */

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Returns the most recent OpenGL error in the queue. */
  GLenum opengl_last_error();

  /** Returns a string for the specified OpenGL error. */
  std::string opengl_error_string(GLenum error);

  /** Throws an exception for the previous OpenGL error, if one exists. */
  void opengl_throw_last_error(const std::string& message);

}

#endif /* OPENGL_HPP */

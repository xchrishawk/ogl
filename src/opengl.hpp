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
#include <glm/gtx/transform.hpp>

/* -- Constants -- */

namespace ogl
{
  extern const glm::vec3 VEC3_ORIGIN;
  extern const glm::vec3 VEC3_UNIT_X;
  extern const glm::vec3 VEC3_UNIT_Y;
  extern const glm::vec3 VEC3_UNIT_Z;

  extern const glm::vec4 VEC4_ORIGIN;
  extern const glm::vec4 VEC4_UNIT_X;
  extern const glm::vec4 VEC4_UNIT_Y;
  extern const glm::vec4 VEC4_UNIT_Z;
  extern const glm::vec4 VEC4_UNIT_W;
}

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Returns the most recent OpenGL error in the queue. */
  GLenum opengl_last_error();

  /** Returns a string for the specified OpenGL error. */
  std::string opengl_error_string(GLenum error);

}

#endif /* OPENGL_HPP */

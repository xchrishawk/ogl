/**
 * glfw.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_GLFW_HPP
#define OGL_OPENGL_GLFW_HPP

/* -- Includes -- */

#include <string>

/* -- Types -- */

namespace ogl
{

  /**
   * Class providing an RAII wrapper for the GLFW library.
   */
  class glfw
  {
  public:

    glfw();
    ~glfw();

    void version(int* major, int* minor, int* revision) const;
    std::string version_string() const;

  private:

    static bool initialized;

    glfw(const glfw& other) = delete;
    glfw& operator =(const glfw& other) = delete;
    static void error_callback(int error, const char* description);

  };

}

#endif /* OGL_OPENGL_GLFW_HPP */

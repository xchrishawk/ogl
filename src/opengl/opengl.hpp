/**
 * opengl.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <GL/gl.h>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract class representing an interface to the OpenGL API.
   */
  class opengl
  {
  public:

    /** Shared pointer to an OpenGL interface object. */
    typedef std::shared_ptr<opengl> ptr;

  protected:

    opengl() { }

  private:

    opengl(const opengl&) = delete;
    opengl& operator =(const opengl&) = delete;

  };

  /**
   * Abstract class for OpenGL interface factories.
   */
  class opengl_factory
  {
  public:

    /** Creates a new OpenGL interface instance. */
    virtual opengl::ptr build() const = 0;

  };

  /**
   * Implementation of `opengl` using GLFW and GLEW.
   */
  class opengl_glfw_glew : public opengl
  {
  public:

    ~opengl_glfw_glew();

  private:

    friend class opengl_glfw_glew_factory;
    opengl_glfw_glew();

  };

  /**
   * Class constructing an OpenGL interface using GLFW and GLEW.
   */
  class opengl_glfw_glew_factory : public opengl_factory
  {
  public:
    virtual opengl::ptr build() const { return opengl::ptr(new opengl_glfw_glew()); }
  };

}

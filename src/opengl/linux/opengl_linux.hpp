/**
 * opengl_linux.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

#if !defined(OGL_LINUX)
  #error This file should only be included on Linux!
#endif

/* -- Includes -- */

#include "opengl/opengl.hpp"
#include "opengl/glfw/glfw.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Interface class for OpenGL on Linux.
   */
  class opengl_linux : public opengl
  {
  public:

    ~opengl_linux();

  private:

    glfw m_glfw;

    friend class opengl_linux_factory;
    opengl_linux();

  };

  /**
   * Factory class for `opengl_linux`.
   */
  class opengl_linux_factory : public opengl_factory
  {
  public:
    virtual opengl::ptr build() const { return opengl::ptr(new opengl_linux()); }
  };

}

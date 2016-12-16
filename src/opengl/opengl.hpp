/**
 * opengl.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include <memory>

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
  class opengl_stub : public opengl
  {
  public:

    ~opengl_stub();

  private:

    friend class opengl_stub_factory;
    opengl_stub();

  };

  /**
   * Class constructing a stub OpenGL interface.
   */
  class opengl_stub_factory : public opengl_factory
  {
  public:
    virtual opengl::ptr build() const { return opengl::ptr(new opengl_stub()); }
  };

}

/**
 * opengl.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include "opengl/api.hpp"

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

    /** Returns the platform default factory. */
    static opengl_factory& platform_default();

    /** Creates a new OpenGL interface instance. */
    virtual opengl::ptr build() const = 0;

  };

}

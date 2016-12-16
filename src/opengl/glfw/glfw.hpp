/**
 * glfw.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * RAII wrapper for the GLFW library.
   */
  class glfw
  {
  public:

    typedef std::shared_ptr<glfw> ptr;
    typedef std::shared_ptr<const glfw> const_ptr;

    ~glfw();

  private:

    friend class glfw_factory;
    glfw();
    glfw(const glfw&) = delete;
    glfw& operator =(const glfw&) = delete;

  };

  /**
   * Factory class for building GLFW instances.
   */
  class glfw_factory
  {
  public:

    /** Returns the platform default factory. */
    static glfw_factory& platform_default();

    /** Creates a new GLFW interface instance. */
    virtual glfw::ptr build() const { return glfw::ptr(new glfw()); }

  };

}

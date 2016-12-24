/**
 * @file	opengl.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract base class for types wrapping the OpenGL interface.
   */
  class opengl
  {
  public:

    /** Shared pointer to an `opengl` instance. */
    typedef std::shared_ptr<opengl> ptr;

    /** Shared pointer to a `const opengl` instance. */
    typedef std::shared_ptr<const opengl> const_ptr;

    virtual ~opengl() { }

  protected:

    opengl() { }

  private:

    opengl(const opengl&) = delete;
    opengl& operator =(const opengl&) = delete;

  };

}

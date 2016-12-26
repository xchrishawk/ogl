/**
 * @file	opengl.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <string>

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

    /* -- Platform Information -- */

    /** Returns the `GL_VERSION` string for the OpenGL implementation. */
    virtual std::string version() const;

    /** Returns the `GL_SHADING_LANGUAGE_VERSION` string for the OpenGL implementation. */
    virtual std::string glsl_version() const;

    /** Returns the `GL_VENDOR` string for the OpenGL implementation. */
    virtual std::string vendor() const;

    /** Returns the `GL_RENDERER` string for the OpenGL implementation. */
    virtual std::string renderer() const;

  protected:

    opengl() { }

  private:

    opengl(const opengl&) = delete;
    opengl& operator =(const opengl&) = delete;

  };

}

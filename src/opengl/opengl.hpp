/**
 * @file	opengl.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <stdexcept>
#include <string>

#include "opengl/shader.hpp"

/* -- Constants -- */

namespace ogl
{

  /**
   * Enumeration of errors which may be returned by OpenGL.
   */
  enum class opengl_error : int
  {
    no_error,
    invalid_enum,
    invalid_value,
    invalid_operation,
    invalid_framebuffer_operation,
    out_of_memory,
    stack_underflow,
    stack_overflow,
    unknown,
  };

}

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing a general OpenGL error.
   */
  class opengl_exception : public std::runtime_error
  {
  public:
    opengl_exception(const std::string& message)
      : std::runtime_error(message)
    { }
  };

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

    /* -- Factory Methods -- */

    /**
     * Creates a new shader instance.
     *
     * @param type
     * The type of shader to create.
     *
     * @exception ogl::opengl_exception
     * Thrown if the shader cannot be created for any reason.
     */
    virtual ogl::shader::ptr create_shader(ogl::shader_type type) const = 0;

    /* -- Platform Information -- */

    /** Returns the `GL_VERSION` string for the OpenGL implementation. */
    virtual std::string version() const = 0;

    /** Returns the `GL_SHADING_LANGUAGE_VERSION` string for the OpenGL implementation. */
    virtual std::string glsl_version() const = 0;

    /** Returns the `GL_VENDOR` string for the OpenGL implementation. */
    virtual std::string vendor() const = 0;

    /** Returns the `GL_RENDERER` string for the OpenGL implementation. */
    virtual std::string renderer() const = 0;

    /* -- Error Handling -- */

    /** Returns the last error registered by the OpenGL interface. */
    virtual ogl::opengl_error last_error() const = 0;

    /** Returns a `std::string` for the specified error enum. */
    virtual std::string error_string(ogl::opengl_error error) const = 0;

  protected:

    opengl() { }

  private:

    opengl(const opengl&) = delete;
    opengl& operator =(const opengl&) = delete;

  };

}

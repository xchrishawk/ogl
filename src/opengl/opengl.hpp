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

#include "opengl/api.hpp"
#include "opengl/buffer.hpp"
#include "opengl/program.hpp"
#include "opengl/shader.hpp"

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
    virtual ogl::shader::ptr create_shader(GLenum type) const = 0;

    /**
     * Creates a new shader program instance.
     *
     * @exception ogl::opengl_exception
     * Thrown if the shader program cannot be created for any reason.
     */
    virtual ogl::program::ptr create_program() const = 0;

    /**
     * Creates a new immutable buffer.
     *
     * @param type
     * The type of buffer to create.
     *
     * @param data
     * The data to load into the buffer, or `nullptr` if the data should be left uninitialized.
     *
     * @param size
     * The size of the buffer, in bytes. Must be greater than or equal to zero.
     *
     * @param flags
     * The flags to use to create the buffer.
     */
    virtual ogl::buffer::ptr create_immutable_buffer(GLenum type,
						     const void* data,
						     size_t size,
						     GLbitfield flags) const = 0;

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
    virtual GLenum last_error() const = 0;

    /** Returns a `std::string` for the specified error enum. */
    virtual std::string error_string(GLenum error) const = 0;

  protected:

    opengl() { }

  private:

    opengl(const opengl&) = delete;
    opengl& operator =(const opengl&) = delete;

  };

}

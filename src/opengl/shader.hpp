/**
 * @file	shader.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <string>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for types representing an OpenGL shader.
   */
  class shader
  {
  public:

    /** Shared pointer to a `shader` object. */
    typedef std::shared_ptr<shader> ptr;

    /** Shared pointer to a `const shader` object. */
    typedef std::shared_ptr<const shader> const_ptr;

    virtual ~shader() { }

    /** Returns the type of this shader. */
    GLenum type() const
    { return m_type; }

    /* -- Abstract Interface -- */

    /** Sets the source code for this shader. */
    virtual void set_source(const std::string& source) = 0;

    /**
     * Compiles the shader.
     *
     * @exception ogl::opengl_exception
     * Thrown if the shader fails to compile for any reason.
     */
    virtual void compile() = 0;

    /** Returns `true` if the shader has been compiled. */
    virtual bool is_compiled() const = 0;

    /** Returns the information log for this shader. */
    virtual std::string info_log() const = 0;

  protected:

    shader(GLenum type)
      : m_type(type)
    { }

  private:

    const GLenum m_type;

    shader(const shader&) = delete;
    shader& operator =(const shader&) = delete;

  };

}

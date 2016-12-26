/**
 * @file	shader.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <string>

/* -- Constants -- */

namespace ogl
{

  /**
   * Enumeration of valid shader types.
   */
  enum class shader_type
  {
    compute_shader,		/**< Equivalent to GL_COMPUTE_SHADER. */
    vertex_shader,		/**< Equivalent to GL_VERTEX_SHADER. */
    tess_control_shader,	/**< Equivalent to GL_TESS_CONTROL_SHADER. */
    tess_evaluation_shader,	/**< Equivalent to GL_TESS_EVALUATION_SHADER. */
    geometry_shader,		/**< Equivalent to GL_GEOMETRY_SHADER. */
    fragment_shader,		/**< Equivalent to GL_FRAGMENT_SHADER. */
  };

}

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
    ogl::shader_type type() const
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

    /** Returns the info log string for this shader. */
    virtual std::string info_log() const = 0;

  protected:

    shader(ogl::shader_type type)
      : m_type(type)
    { }

  private:

    const ogl::shader_type m_type;

    shader(const shader&) = delete;
    shader& operator =(const shader&) = delete;

  };

}

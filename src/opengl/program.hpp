/**
 * @file	program.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <string>
#include <vector>

#include "opengl/api.hpp"
#include "opengl/shader.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing an OpenGL shader program.
   */
  class program
  {
  public:

    /** Shared pointer to an `ogl::program` object. */
    typedef std::shared_ptr<program> ptr;

    /** Shared pointer to a constant `ogl::program` object. */
    typedef std::shared_ptr<const program> const_ptr;

    /**
     * Creates a new OpenGL program.
     *
     * @exception ogl::alloc_exception
     * Thrown if a new program object cannot be created.
     */
    static ptr create();

    /** Sets the specified program as the currently active shader program. */
    static void use(const program::const_ptr& program);

    /** Deactivates the currently active shader program, if there is one. */
    static void use_none();

    ~program();

    /**
     * Links this shader program.
     *
     * @param shaders
     * A `std::vector` of `ogl::shader` objects to include.
     *
     * @exception ogl::shader_exception
     * Thrown if the program cannot be linked for any reason.
     */
    void link(const std::vector<shader::ptr>& shaders);

    /** Returns the internal OpenGL handle for this program. */
    GLuint handle() const { return m_handle; }

    /** Returns `true` if the shader program has been succesfully compiled. */
    bool is_linked() const;

    /** Returns the OpenGL info log string for this shader. */
    std::string info_log() const;

    /**
     * Returns the location for the vertex attribute with the specified name,
     * or -1 if no matching vertex attribute is found.
     */
    GLint attribute_location(const std::string& name) const;

    /**
     * Returns the location for the uniform with the specified name, or -1 if no
     * matching uniform is found.
     */
    GLint uniform_location(const std::string& name) const;

  private:

    const GLuint m_handle;

    program();
    program(const program& other) = delete;
    program& operator =(const program& other) = delete;

    static GLuint new_handle();

  };

}

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

    /**
     * Creates a new OpenGL program.
     *
     * @exception ogl::alloc_exception
     * Thrown if a new program object cannot be created.
     */
    static ptr create();

    /** Deactivates the currently active OpenGL program, if there is one. */
    static void deactivate();

    ~program();

    /** Attaches a shader to this program. */
    void attach_shader(ogl::shader::const_ptr shader);

    /** Detaches a shader from this program. */
    void detach_shader(ogl::shader::const_ptr shader);

    /**
     * Links this shader program.
     *
     * @exception ogl::shader_exception
     * Thrown if the program cannot be linked for any reason.
     */
    void link();

    /** Makes this program the currently active OpenGL program. */
    void activate() const;

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
    GLint attribute_location(const std::string& name);

    /**
     * Returns the location for the uniform with the specified name, or -1 if no
     * matching uniform is found.
     */
    GLint uniform_location(const std::string& name);

  private:

    const GLuint m_handle;

    program();
    program(const program& other) = delete;
    program& operator =(const program& other) = delete;

    static GLuint new_handle();

  };

}

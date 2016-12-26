/**
 * @file	program.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <vector>

#include "opengl/shader.hpp"

/* -- Constants -- */

namespace
{
  /** The index returned for an invalid attribute or uniform. */
  const int OPENGL_INVALID_INDEX = -1;
}

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for types representing an OpenGL shader program.
   */
  class program
  {
  public:

    /** Shared pointer to a `program` object. */
    typedef std::shared_ptr<program> ptr;

    /** Shared pointer to a `const program` object. */
    typedef std::shared_ptr<const program> const_ptr;

    virtual ~program() { }

    /* -- Abstract Interface -- */

    /**
     * Links this program with the specified shaders.
     *
     * @param shaders
     * A `std::vector` of shaders to include in the program.
     *
     * @exception ogl::opengl_exception
     * Thrown if the program cannot be linked for any reason.
     */
    virtual void link(const std::vector<ogl::shader::const_ptr>& shaders) = 0;

    /** Returns `true` if this shader program has been linked. */
    virtual bool is_linked() const = 0;

    /** Returns the number of active attributes in this program. */
    virtual int attribute_count() const = 0;

    /** Returns the index of the attribute with the specified name. */
    virtual int attribute_index(const std::string& name) const = 0;

    /** Returns the number of active uniforms in this program. */
    virtual int uniform_count() const = 0;

    /** Returns the index of the uniform with the specified name. */
    virtual int uniform_index(const std::string& name) const = 0;

    /** Returns the information log for this shader program. */
    virtual std::string info_log() const = 0;

  protected:

    program() { }

  private:

    program(const program&) = delete;
    program& operator =(const program&) = delete;

  };

}

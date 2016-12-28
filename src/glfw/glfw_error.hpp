/**
 * @file	glfw_error.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

#pragma once

/* -- Includes -- */

#include <exception>

/* -- Types -- */

namespace glfw
{

  /**
   * Class representing an error thrown by the GLFW library.
   */
  class glfw_error : std::exception
  {
  public:

    /**
     * Constructs a new instance.
     *
     * @param error
     * The GLFW error code.
     *
     * @param description
     * A string describing the error.
     */
    glfw_error(int error, const char* description)
      : error_(error),
        description_(description)
    { }

    /** Returns the GLFW error code. */
    int error() const
    { return error_; }

    /** Returns the GLFW error description. */
    std::string description() const
    { return description_; }

    /** Returns a string describing the error. */
    virtual const char* what() const noexcept override
    { return description_.c_str(); }

  private:

    int error_;
    std::string description_;

  };

}

/**
 * @file	exceptions.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Includes -- */

#include <exception>
#include <stdexcept>

/* -- Types -- */

namespace ogl
{

  /**
   * Exception thrown when an OpenGL object cannot be created for any reason.
   */
  class alloc_exception : public std::runtime_error
  {
  public:
    alloc_exception(const std::string& message)
      : std::runtime_error(message)
    { }
  };

  /**
   * Exception thrown when a file I/O operation cannot be completed.
   */
  class file_io_exception : public std::runtime_error
  {
  public:
    file_io_exception(const std::string& message)
      : std::runtime_error(message)
    { }
  };

  /**
   * Exception thrown when a shader program cannot be loaded or compiled.
   */
  class shader_exception : public std::runtime_error
  {
  public:
    shader_exception(const std::string& message)
      : std::runtime_error(message)
    { }
  };

}

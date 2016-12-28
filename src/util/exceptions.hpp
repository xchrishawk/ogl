/**
 * @file	exceptions.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <exception>
#include <stdexcept>
#include <string>

/* -- Types -- */

namespace ogl
{

  /**
   * Exception thrown when multiple copies of an object that should have only a
   * single instance are created.
   */
  class duplicate_object_exception
    : public std::runtime_error
  {
  public:
    duplicate_object_exception(const std::string& message)
      : std::runtime_error(message)
    { }
  };

  /**
   * Exception thrown when a library cannot be initialized.
   */
  class library_init_exception
    : public std::runtime_error
  {
  public:
    library_init_exception(const std::string& message)
      : std::runtime_error(message)
    { }
  }

}

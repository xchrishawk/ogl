/**
 * @file	resource_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

#pragma once

/* -- Includes -- */

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

/* -- Types -- */

namespace ogl
{

  /**
   * Exception thrown when a resource cannot be loaded.
   */
  class resource_exception : public std::runtime_error
  {
  public:
    resource_exception(const std::string& message)
      : std::runtime_error(message)
    { }
  };

  /**
   * Class responsible for managing application resources.
   */
  class resource_manager
  {
  public:

    /** Shared pointer to a `resource_manager` instance. */
    typedef std::shared_ptr<resource_manager> ptr;

    /** Shared pointer to a `const resource_manager` instance. */
    typedef std::shared_ptr<const resource_manager> const_ptr;

    /** Returns a shared pointer to a new resource manager instance. */
    static resource_manager::ptr create();

    /**
     * Returns the source code for the shader with the specified filename.
     *
     * @exception ogl::resource_exception
     * Thrown if the resource cannot be loaded.
     */
    std::string shader_source(const std::string& filename) const;

  private:

    const std::map<std::string, std::string> m_shaders;

    resource_manager(const std::map<std::string, std::string>& shaders);
    resource_manager(const resource_manager&) = delete;
    resource_manager& operator =(const resource_manager&) = delete;

  };

}

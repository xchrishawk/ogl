/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include "app/window_manager.hpp"
#include "glfw/api.hpp"

/* -- Types -- */

namespace glfw
{

  /**
   * Struct containing arguments used to construct a `glfw::window_manager` instance.
   */
  struct window_manager_args final
  {
    glfw::api::ptr api;
  };

  /**
   * Concrete implementation of `ogl::window_manager` using the GLFW library.
   */
  class window_manager final
    : public ogl::window_manager
  {
  public:

    /** Shared pointer to a `glfw::window_manager` instance. */
    typedef std::shared_ptr<window_manager> ptr;

    /** Shared pointer to a `const glfw::window_manager` instance. */
    typedef std::shared_ptr<const window_manager> const_ptr;

    /**
     * Creates a shared pointer to a new `glfw::window_manager` instance.
     *
     * @param args
     * Struct containing arguments required to initialize the GLFW library.
     *
     * @exception std::invalid_argument
     * Thrown if any argument is invalid.
     *
     * @exception ogl::duplicate_object_exception
     * Thrown if there is already an active GLFW window manager object.
     *
     * @exception ogl::library_init_exception
     * Thrown if the library cannot be initialized.
     */
    static glfw::window_manager::ptr create(const glfw::window_manager_args& args);

    virtual ~window_manager();

    /** Returns a version string for the GLFW library. */
    virtual std::string version() const;

  private:

    static glfw::window_manager* instance_s;
    glfw::api::ptr api_;

    static void error_callback(int error, const char* description);

    window_manager(const glfw::window_manager_args& args);
    window_manager(const glfw::window_manager&) = delete;
    glfw::window_manager& operator =(const glfw::window_manager&) = delete;

  };

}

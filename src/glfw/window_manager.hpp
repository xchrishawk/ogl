/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include "app/window_manager.hpp"
#include "glfw/api.hpp"
#include "glfw/glfw_error.hpp"

/* -- Types -- */

namespace glfw
{

  /**
   * Struct containing arguments used to construct a `glfw::window_manager` instance.
   */
  struct window_manager_args final
  {
    std::shared_ptr<glfw::api> api;
  };

  /**
   * Concrete implementation of `ogl::window_manager` using the GLFW library.
   */
  class window_manager final : public ogl::window_manager
  {
  public:

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
     * @exception glfw::glfw_error
     * Thrown if the library cannot be initialized.
     */
    static auto create(const glfw::window_manager_args& args)
    {
      return std::shared_ptr<glfw::window_manager>(new glfw::window_manager(args));
    }

    virtual ~window_manager();

    /** Returns a version string for the GLFW library. */
    virtual std::string version() const;

  private:

    static glfw::window_manager* instance_s;
    static std::shared_ptr<glfw::glfw_error> last_error_s;

    static void error_callback(int error, const char* description);
    static void throw_last_error() __attribute__((noreturn));

    std::shared_ptr<glfw::api> api_;

    window_manager(const glfw::window_manager_args& args);
    window_manager(const glfw::window_manager&) = delete;
    glfw::window_manager& operator =(const glfw::window_manager&) = delete;

  };

}

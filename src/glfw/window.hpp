/**
 * @file	window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

#pragma once

/* -- Includes -- */

#include <memory>

#include "app/window.hpp"
#include "glfw/api.hpp"
#include "glfw/window_manager.hpp"

/* -- Types -- */

namespace glfw
{

  /**
   * Struct containing information required to build a `glfw::window` instance.
   */
  struct window_args
  {
    std::shared_ptr<glfw::api> api;
    std::shared_ptr<glfw::window_manager> window_manager;
  };

  /**
   * Class representing a GLFW window.
   */
  class window : public app::window
  {
  public:

    /**
     * Returns a shared pointer to a new GLFW window instance.
     *
     * @param args
     * A struct containing arguments required to construct the window.
     */
    static std::shared_ptr<glfw::window> create(const glfw::window_args& args)
    {
      return std::shared_ptr<glfw::window>(new glfw::window(args));
    }

    virtual ~window();

  private:

    const std::shared_ptr<glfw::api> api_;
    const std::shared_ptr<glfw::window_manager> window_manager_;

    window(const glfw::window_args& args);
    window(const glfw::window&) = delete;
    glfw::window& operator =(const glfw::window&) = delete;

  };

}

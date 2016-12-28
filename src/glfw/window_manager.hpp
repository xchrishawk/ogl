/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include "app/window_manager.hpp"

/* -- Types -- */

namespace glfw
{

  /**
   * Struct containing arguments used to construct a `glfw::window_manager` instance.
   */
  struct window_manager_args final
  {
  };

  /**
   * Concrete implementation of `ogl::window_manager` using the GLFW library.
   */
  class window_manager final
    : public ogl::window_manager
  {
  public:

    /**
     * Creates a shared pointer to a new `glfw::window_manager` instance.
     *
     * @param args
     * Struct containing arguments required to initialize the GLFW library.
     *
     * @exception ogl::duplicate_object_exception
     * Thrown if there is already an active GLFW window manager object.
     *
     * @exception ogl::library_init_exception
     * Thrown if the library cannot be initialized.
     */
    static ogl::window_manager::ptr create(const glfw::window_manager_args& args);

    virtual ~window_manager();

  private:

    static glfw::window_manager* instance_s;

    window_manager(const glfw::window_manager_args& args);
    window_manager(const glfw::window_manager&) = delete;
    glfw::window_manager& operator =(const glfw::window_manager&) = delete;

  };

}

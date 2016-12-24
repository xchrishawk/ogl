/**
 * @file	glfw_window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <GLFW/glfw3.h>
#include "window/window.hpp"

/* -- Types -- */

namespace ogl
{
  namespace glfw
  {

    /**
     * Struct containing arguments used to create a GLFW window.
     */
    struct glfw_window_args
    {
      std::string title;		/**< The window's initial title. */
      int width;			/**< The window's initial width. */
      int height;			/**< The window's initial height. */
    };

    /**
     * Class representing a GLFW window.
     */
    class glfw_window final : public window
    {
    public:

      /**
       * Creates a shared pointer to a new `glfw_window` instance.
       *
       * @param args
       * A struct containing the information required to create the window.
       */
      static ogl::window::ptr create(const glfw_window_args& args);

      ~glfw_window();

      /* -- window -- */

      virtual bool is_current_context() const;
      virtual void make_current_context();
      virtual void swap_buffers();
      virtual bool should_close() const;
      virtual void set_should_close(bool should_close);
      virtual std::string title() const;
      virtual void set_title(const std::string& title);

    private:

      GLFWwindow* m_handle;
      std::string m_title;

      glfw_window(const glfw_window_args& args);

    };

  }
}

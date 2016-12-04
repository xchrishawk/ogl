/**
 * window.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

/* -- Includes -- */

#include <string>
#include "opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class for the application's main window.
   */
  class window
  {
  public:

    window(int context_version_major,
	   int context_version_minor,
	   int initial_width,
	   int initial_height,
	   const std::string& initial_title,
	   GLFWkeyfun key_callback);
    ~window();

    bool should_close() const;
    void set_should_close(bool value);
    void swap_buffers() const;

    static void poll_events();

  private:

    GLFWwindow* m_window;

    window(const window& other) = delete;
    window& operator =(const window& other) = delete;

  };

}

#endif /* WINDOW_HPP */

/**
 * window.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_WINDOW_HPP
#define OGL_OPENGL_WINDOW_HPP

/* -- Includes -- */

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    void framebuffer_size(int* width, int* height) const;

    static void poll_events();

  private:

    GLFWwindow* m_window;

    window(const window& other) = delete;
    window& operator =(const window& other) = delete;

  };

}

#endif /* OGL_OPENGL_WINDOW_HPP */

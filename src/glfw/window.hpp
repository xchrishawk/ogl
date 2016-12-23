
/**
 * @file	window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include "opengl/api.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Wrapper for a GLFW window.
   */
  class window
  {
  public:

    typedef std::shared_ptr<window> ptr;
    typedef std::shared_ptr<const window> const_ptr;

    /** Creates and returns a shared pointer to a new `window` instance. */
    static window::ptr create(bool make_current,
			      int initial_width,
			      int initial_height,
			      const std::string& initial_title);

    ~window();

    /** Returns `true` if the window should close. */
    bool should_close() const;

    /** Sets the should close flag. */
    void set_should_close(bool should_close);

    /** Swaps the window's frame buffer with the OpenGL back buffer. */
    void swap_buffers();

    /** Sets the keypress callback for this window. */
    void set_key_callback(GLFWkeyfun callback);

    /** Gets the state of the specified key. */
    bool get_key(int key) const;

    /** Makes this window the current OpenGL context. */
    void make_context_current();

    /** Returns `true` if this window is the current OpenGL context. */
    bool is_context_current() const;

    /** Gets the size of the window's framebuffer. */
    void framebuffer_size(int* width, int* height) const;

  private:

    GLFWwindow* m_handle;

    window(bool make_current,
	   int initial_width,
	   int initial_height,
	   const std::string& initial_title);
    window(const window&) = delete;
    window& operator =(const window&) = delete;

  };

}

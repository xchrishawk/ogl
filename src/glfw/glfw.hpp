/**
 * @file	glfw.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  /**
   * RAII wrapper for the GLFW library.
   */
  class glfw
  {
  public:

    glfw();
    ~glfw();

    /** The current GLFW timer value, in seconds. */
    double time() const;

    /** Polls GLFW for events. */
    void poll_events() const;

    /** Waits for the next GLFW events. */
    void wait_events() const;

    /** Sets the swap interval for the currently active OpenGL context. */
    void set_swap_interval(int interval);

  private:

    glfw(const glfw&) = delete;
    glfw& operator =(const glfw&) = delete;

    void print_version_info();

    static glfw* s_instance;
    static void error_callback(int error, const char* description);

  };

}

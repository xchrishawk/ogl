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

    /** Polls GLFW for events. */
    void poll_events() const;

    /** Waits for the next GLFW events. */
    void wait_events() const;

  private:

    glfw(const glfw&) = delete;
    glfw& operator =(const glfw&) = delete;

    static glfw* s_instance;
    static void error_callback(int error, const char* description);

  };

}

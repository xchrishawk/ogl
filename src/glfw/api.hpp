/**
 * @file	api.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <GLFW/glfw3.h>

/* -- Types -- */

namespace glfw
{

  /**
   * Class wrapping the GLFW C API.
   *
   * This is mostly intended for unit testing, so we can stub out the API when we need to simulate
   * specific behavior. In the default implementation, each method just forwards directly to the
   * corresponding C API function.
   */
  class api
  {
  public:

    /** Returns a shared pointer to a new `glfw::api` instance. */
    static auto create()
    {
      return std::shared_ptr<glfw::api>(new glfw::api());
    }

    virtual ~api() = default;

    /* -- GLFW Library Functions -- */

    /** Forwards to `glfwInit()`. */
    virtual int init() const
    {
      return glfwInit();
    }

    /** Forwards to `glfwTerminate()`. */
    virtual void terminate() const
    {
      glfwTerminate();
    }

    /** Forwards to `glfwSetErrorCallback()`. */
    virtual void set_error_callback(GLFWerrorfun cbfun) const
    {
      glfwSetErrorCallback(cbfun);
    }

    /** Forwards to `glfwGetVersionString()`. */
    virtual const char* get_version_string() const
    {
      return glfwGetVersionString();
    }

    /** Forwards to `glfwGetTime()`. */
    virtual double get_time() const
    {
      return glfwGetTime();
    }

    /** Forwards to `glfwPollEvents()`. */
    virtual void poll_events() const
    {
      glfwPollEvents();
    }

    /** Forwards to `glfwCreateWindow()`. */
    virtual GLFWwindow* create_window(int width,
                                      int height,
                                      const char* title,
                                      GLFWmonitor* monitor,
                                      GLFWwindow* share) const
    {
      return glfwCreateWindow(width, height, title, monitor, share);
    }

    /** Forwards to `glfwDestroyWindow()`. */
    virtual void destroy_window(GLFWwindow* window) const
    {
      glfwDestroyWindow(window);
    }

    /** Forwards to `glfwGetCurrentContext()`. */
    virtual GLFWwindow* get_current_context() const
    {
      return glfwGetCurrentContext();
    }

    /** Forwards to `glfwMakeContextCurrent()`. */
    virtual void make_context_current(GLFWwindow* window) const
    {
      glfwMakeContextCurrent(window);
    }

    /** Forwards to `glfwSwapBuffers()`. */
    virtual void swap_buffers(GLFWwindow* window) const
    {
      glfwSwapBuffers(window);
    }

    /** Forwards to `glfwWindowShouldClose()`. */
    virtual int window_should_close(GLFWwindow* window) const
    {
      return glfwWindowShouldClose(window);
    }

    /** Forwards to `glfwSetWindowShouldClose()`. */
    virtual void set_window_should_close(GLFWwindow* window, int value) const
    {
      glfwSetWindowShouldClose(window, value);
    }

  protected:

    api() = default;

  private:

    api(const glfw::api&) = delete;
    glfw::api& operator =(const glfw::api&) = delete;

  };

}

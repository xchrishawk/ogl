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
   * @note
   * This is mostly intended for unit testing, so we can stub out the API when
   * we need to simulate specific behavior.
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
    { return glfwInit(); }

    /** Forwards to `glfwTerminate()`. */
    virtual void terminate() const
    { glfwTerminate(); }

    /** Forwards to `glfwSetErrorCallback()`. */
    virtual void set_error_callback(GLFWerrorfun cbfun) const
    { glfwSetErrorCallback(cbfun); }

    /** Forwards to `glfwGetVersionString()`. */
    virtual const char* get_version_string() const
    { return glfwGetVersionString(); }

  protected:

    api() = default;

  private:

    api(const glfw::api&) = delete;
    glfw::api& operator =(const glfw::api&) = delete;

  };

}

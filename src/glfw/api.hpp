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

    virtual int init()
    { return ::glfwInit(); }

    virtual void terminate()
    { ::glfwTerminate(); }

    virtual void set_error_callback(GLFWerrorfun cbfun)
    { ::glfwSetErrorCallback(cbfun); }

    virtual const char* get_version_string()
    { return ::glfwGetVersionString(); }

  protected:

    api() = default;

  private:

    api(const glfw::api&) = delete;
    glfw::api& operator =(const glfw::api&) = delete;

  };

}

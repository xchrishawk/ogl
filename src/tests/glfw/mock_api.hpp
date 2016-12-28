/**
 * @file	mock_api.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <functional>
#include <memory>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"

/* -- Types -- */

namespace glfw
{

  /**
   * Mock GLFW API class.
   */
  class mock_api final
    : public glfw::api
  {
  public:

    static auto create() { return std::shared_ptr<glfw::mock_api>(new glfw::mock_api()); }

    /* -- Mock Methods -- */

    virtual int init()
    { return impl_init(); }

    virtual void terminate()
    { impl_terminate(); }

    virtual void set_error_callback(GLFWerrorfun cbfun)
    { impl_set_error_callback(cbfun); }

    virtual const char* get_version_string()
    { return impl_get_version_string(); }

    /* -- Lambdas -- */

    std::function<int(void)> impl_init = [] () { return 1; };
    std::function<void(void)> impl_terminate = [] () { };
    std::function<void(GLFWerrorfun)> impl_set_error_callback = [] (GLFWerrorfun) { };
    std::function<const char*(void)> impl_get_version_string = [] () { return "Mock API"; };

  };

}

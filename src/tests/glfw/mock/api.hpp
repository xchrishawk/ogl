/**
 * @file	api.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <functional>
#include <memory>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "util/debug.hpp"

/* -- Types -- */

namespace glfw
{
  namespace mock
  {

    /**
     * Mock GLFW API class.
     *
     * This is used for unit testing the wrapper around the GLFW library. The implementation
     * for each method may be overridden/modified by setting the corresponding lambda.
     */
    class api final : public glfw::api
    {
    public:

      static auto create()
      {
        return std::shared_ptr<glfw::mock::api>(new glfw::mock::api());
      }

      /* -- Mock Methods -- */

      virtual int init() const override
      { ogl_dbg_status("hello!"); return init_lambda(); }

      virtual void terminate() const override
      { terminate_lambda(); }

      virtual void set_error_callback(GLFWerrorfun cbfun) const override
      { set_error_callback_lambda(cbfun); }

      virtual const char* get_version_string() const override
      { return get_version_string_lambda(); }

      /* -- Lambdas -- */

      std::function<int(void)> init_lambda = [] { return 1; };
      std::function<void(void)> terminate_lambda = [] { };
      std::function<void(GLFWerrorfun)> set_error_callback_lambda = [] (GLFWerrorfun) { };
      std::function<const char*(void)> get_version_string_lambda = [] { return "Mock API"; };

    private:

      api() = default;
      api(const glfw::mock::api&) = delete;
      glfw::mock::api& operator =(const glfw::mock::api&) = delete;

    };

  }
}

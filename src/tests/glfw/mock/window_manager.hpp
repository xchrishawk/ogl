/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <gmock/gmock.h>

#include "glfw/window_manager.hpp"

/* -- Types -- */

namespace glfw
{
  namespace mock
  {

    /**
     * Mock class for the GLFW window manager.
     */
    class window_manager : public glfw::window_manager
    {
    public:

      /** Returns a shared pointer to a new `glfw::mock::window_manager` instance. */
      static auto create(const glfw::window_manager_args& args)
      {
        return std::shared_ptr<glfw::mock::window_manager>(new glfw::mock::window_manager(args));
      }

      /* -- Mock Methods -- */

      MOCK_CONST_METHOD0(time, double());
      MOCK_CONST_METHOD0(poll_events, void());

    private:

      window_manager(const glfw::window_manager_args& args)
        : glfw::window_manager(args)
      { }

    };

  }
}

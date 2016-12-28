/**
 * @file	api.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <gmock/gmock.h>

#include "glfw/api.hpp"

/* -- Types -- */

namespace glfw
{
  namespace mock
  {

    /**
     * Mock class for the GLFW API.
     *
     * This is intended to allow stubbing/modifying methods from the GLFW API to support unit
     * testing of the GLFW wrapper.
     */
    class api : public glfw::api
    {
    public:

      /** Create a shared pointer to a new mock API instance. */
      static auto create()
      {
        return std::shared_ptr<glfw::mock::api>(new glfw::mock::api());
      }

      /* -- Mock Methods -- */

      MOCK_CONST_METHOD0(init, int());
      MOCK_CONST_METHOD0(terminate, void());
      MOCK_CONST_METHOD1(set_error_callback, void(GLFWerrorfun cbfun));
      MOCK_CONST_METHOD0(get_version_string, const char*());
      MOCK_CONST_METHOD0(get_time, double());
      MOCK_CONST_METHOD0(poll_events, void());

      /* -- Stored State -- */

      GLFWerrorfun error_callback = nullptr;

    };

  }
}

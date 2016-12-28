/*
 * @file	window_tests.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

/* -- Includes -- */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "glfw/window.hpp"
#include "tests/glfw/mock/api.hpp"
#include "tests/glfw/mock/window_manager.hpp"

/* -- Namespaces -- */

using namespace glfw;
using namespace testing;

/* -- GLFWWindow -- */

/**
 * Unit test checking initialization of the `glfw::window` class.
 */
class GLFWWindow : public Test
{
protected:

  std::shared_ptr<mock::api> api_;
  std::shared_ptr<mock::window_manager> window_manager_;
  GLFWerrorfun error_callback;

  virtual void SetUp() override
  {
    // create API
    api_ = mock::api::create();
    EXPECT_CALL(*api_, init())
      .WillOnce(Return(1));
    EXPECT_CALL(*api_, set_error_callback(Ne(nullptr)))
      .WillOnce(SaveArg<0>(&error_callback));

    // create window manager
    glfw::window_manager_args args;
    args.api = api_;
    window_manager_ = mock::window_manager::create(args);
  }

  virtual void TearDown() override
  {
    EXPECT_CALL(*api_, terminate());
  }

  std::shared_ptr<window> make_window()
  {
    glfw::window_args args;
    args.api = api_;
    args.window_manager = window_manager_;
    return window::create(args);
  }

};

/**
 * Verify that a `std::invalid_argument` exception is thrown if the API is null.
 */
TEST_F(GLFWWindow, ExceptionThrownOnInitializationIfAPIIsNull)
{
  try
  {
    glfw::window_args args;
    args.api = nullptr;
    args.window_manager = window_manager_;
    auto window = window::create(args);
    ADD_FAILURE();
  }
  catch (const std::invalid_argument&)
  {
    SUCCEED();
  }
}

/**
 * Verify that a `std::invalid_argument` exception is thrown if the window manager is null.
 */
TEST_F(GLFWWindow, ExceptionThrownOnInitializationIfWindowManagerIsNull)
{
  try
  {
    glfw::window_args args;
    args.api = api_;
    args.window_manager = nullptr;
    auto window = window::create(args);
    ADD_FAILURE();
  }
  catch (const std::invalid_argument&)
  {
    SUCCEED();
  }
}

/**
 * @file	window_manager_tests.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "tests/glfw/mock/api.hpp"
#include "util/exceptions.hpp"

/* -- Namespaces -- */

using namespace glfw;
using namespace testing;

/* -- Helper Functions -- */

namespace
{

  /** Create a window manager with the specified api. */
  auto make_window_manager(const std::shared_ptr<mock::api>& api)
  {
    window_manager_args args;
    args.api = api;
    return window_manager::create(args);
  }

  /** Expects that `init()` will be called once. */
  inline void expect_init(const std::shared_ptr<glfw::mock::api>& api)
  {
    EXPECT_CALL(*api, init())
      .WillOnce(Return(1));
  }

  /** Expects that `terminate()` will be called once. */
  inline void expect_terminate(const std::shared_ptr<glfw::mock::api>& api)
  {
    EXPECT_CALL(*api, terminate());
  }

  /** Expects that `set_error_callback()` will be called once. */
  inline void expect_set_error_callback(const std::shared_ptr<glfw::mock::api>& api)
  {
    EXPECT_CALL(*api, set_error_callback(Ne(nullptr)))
      .WillOnce(SaveArg<0>(&(*api).error_callback));
  }

  /** Expects that `get_version_string()` will be called any number of times. */
  inline void expect_get_version_string(const std::shared_ptr<glfw::mock::api>& api)
  {
    EXPECT_CALL(*api, get_version_string())
      .WillOnce(Return("Mock GLFW API"));
  }

  /** Expects that the entire API lifecycle will occur. */
  inline void expect_lifecycle(const std::shared_ptr<glfw::mock::api>& api)
  {
    expect_set_error_callback(api);
    expect_init(api);
    expect_get_version_string(api);
    expect_terminate(api);
  }

}

/* -- Test Cases -- */

/**
 * Verify that a `std::invalid_argument` exception is thrown if the API object is null.
 */
TEST(GLFWWindowManager, ExceptionThrownOnInitializationIfAPIIsNull)
{
  try
  {
    auto window_manager = make_window_manager(nullptr);
    ADD_FAILURE();
  }
  catch (const std::invalid_argument&)
  {
    SUCCEED();
  }
}

/**
 * Verify that a `glfw::glfw_error` exception is thrown if the GLFW library fails to initialize.
 */
TEST(GLFWWindowManager, ExceptionThrownOnInitializationIfGLFWFailsToInitialize)
{
  static const int EXPECTED_ERROR = 123;
  static const std::string EXPECTED_DESCRIPTION = "GLFW Failure";

  auto api = mock::api::create();
  expect_set_error_callback(api);
  EXPECT_CALL(*api, init())
    .Times(1)
    .WillOnce(Invoke([&api] () {
          api->error_callback(EXPECTED_ERROR, EXPECTED_DESCRIPTION.c_str());
          return 0;
        }));

  try
  {
    auto window_manager = make_window_manager(api);
    ADD_FAILURE();
  }
  catch (const glfw::glfw_error& error)
  {
    EXPECT_EQ(error.error(), EXPECTED_ERROR);
    EXPECT_EQ(error.description(), EXPECTED_DESCRIPTION);
  }
}

/**
 * Verify that an `ogl::duplicate_object_exception` is thrown if the GLFW window manager is
 * initialized while another instance is already active.
 */
TEST(GLFWWindowManager, ExceptionThrownOnInitializationIfGLFWIsAlreadyInitialized)
{
  auto api = mock::api::create();
  expect_lifecycle(api);

  try
  {
    auto window_manager = make_window_manager(api);
    auto duplicate_window_manager = make_window_manager(api);
    ADD_FAILURE();
  }
  catch (ogl::duplicate_object_exception&)
  {
    SUCCEED();
  }
}

/**
 * Verify that GLFW can be reinitialized after it has been deinitialized.
 */
TEST(GLFWWindowManager, WindowManagerCanReinitializeAfterDeinitializing)
{
  InSequence seq;

  auto api = mock::api::create();
  expect_lifecycle(api);
  expect_lifecycle(api);

  try
  {
    // for scope
    {
      auto first_window_manager = make_window_manager(api);
    }
    auto second_window_manager = make_window_manager(api);
    SUCCEED();
  }
  catch (ogl::duplicate_object_exception&)
  {
    ADD_FAILURE();
  }
}

/**
 * Verify that the window manager returns the correct time from the API.
 */
TEST(GLFWWindowManager, ReturnsCorrectTime)
{
  static const double EXPECTED_TIME = 40.0;

  auto api = mock::api::create();
  expect_lifecycle(api);
  EXPECT_CALL(*api, get_time())
    .Times(1)
    .WillOnce(Return(EXPECTED_TIME));

  auto window_manager = make_window_manager(api);
  EXPECT_EQ(window_manager->time(), EXPECTED_TIME);
}

/**
 * Verify that the window manager polls events from the API.
 */
TEST(GLFWWindowManager, PollsEvents)
{
  auto api = mock::api::create();
  expect_lifecycle(api);
  EXPECT_CALL(*api, poll_events())
    .Times(1);

  auto window_manager = make_window_manager(api);
  window_manager->poll_events();
}

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

/* -- Namespaces -- */

using namespace glfw;
using namespace testing;

/* -- GLFWWindowManagerInitialization -- */

/**
 * Unit test checking initialization of the `glfw::window_manager` class.
 */
class GLFWWindowManager : public Test
{
protected:

  std::shared_ptr<mock::api> api_;
  GLFWerrorfun error_callback;

  virtual void SetUp() override
  {
    api_ = mock::api::create();
  }

  std::shared_ptr<window_manager> make_window_manager()
  {
    window_manager_args args;
    args.api = api_;
    return window_manager::create(args);
  }

  void expect_call_init()
  {
    EXPECT_CALL(*api_, init())
      .WillOnce(Return(1));
  }

  void expect_call_terminate()
  {
    EXPECT_CALL(*api_, terminate());
  }

  void expect_call_set_error_callback()
  {
    EXPECT_CALL(*api_, set_error_callback(Ne(nullptr)))
      .WillOnce(SaveArg<0>(&error_callback));
  }

  void expect_call_all()
  {
    expect_call_set_error_callback();
    expect_call_init();
    expect_call_terminate();
  }

};

/**
 * Verify that a `std::invalid_argument` exception is thrown if the API object is null.
 */
TEST_F(GLFWWindowManager, ExceptionThrownOnInitializationIfAPIIsNull)
{
  try
  {
    api_ = nullptr;
    auto window_manager = make_window_manager();
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
TEST_F(GLFWWindowManager, ExceptionThrownOnInitializationIfGLFWFailsToInitialize)
{
  static const int EXPECTED_ERROR = 123;
  static const std::string EXPECTED_DESCRIPTION = "GLFW Failure";

  expect_call_set_error_callback();
  EXPECT_CALL(*api_, init())
    .Times(1)
    .WillOnce(Invoke([this] () {
          error_callback(EXPECTED_ERROR, EXPECTED_DESCRIPTION.c_str());
          return 0;
        }));

  try
  {
    auto window_manager = make_window_manager();
    ADD_FAILURE();
  }
  catch (const glfw::glfw_error& error)
  {
    EXPECT_EQ(error.error(), EXPECTED_ERROR);
    EXPECT_EQ(error.description(), EXPECTED_DESCRIPTION);
  }
}

/**
 * Verify that a `std::logic_error` exception is thrown if the GLFW window manager is initialized
 * while another instance is already active.
 */
TEST_F(GLFWWindowManager, ExceptionThrownOnInitializationIfGLFWIsAlreadyInitialized)
{
  expect_call_all();

  try
  {
    auto window_manager = make_window_manager();
    auto duplicate_window_manager = make_window_manager();
    ADD_FAILURE();
  }
  catch (const std::logic_error&)
  {
    SUCCEED();
  }
}

/**
 * Verify that a new window manager can be initialized if the previous window manager has been
 * deinitialized.
 */
TEST_F(GLFWWindowManager, ReinitializesAfterDeinitializing)
{
  InSequence seq;
  expect_call_all();
  expect_call_all();

  try
  {
    // for scope
    {
      auto first_window_manager = make_window_manager();
    }
    auto second_window_manager = make_window_manager();
    SUCCEED();
  }
  catch (const std::logic_error&)
  {
    ADD_FAILURE();
  }
}

/**
 * Verify that the static `is_initialized()` method returns `true` if the window manager has already
 * been initialized.
 */
TEST_F(GLFWWindowManager, ReturnsIsInitialized)
{
  EXPECT_EQ(window_manager::is_initialized(), false);

  expect_call_all();

  // scope
  {
    auto window_manager = make_window_manager();
    EXPECT_EQ(window_manager::is_initialized(), true);
  }

  EXPECT_EQ(window_manager::is_initialized(), false);
}

/**
 * Verify that the window manager returns the API's version string.
 */
TEST_F(GLFWWindowManager, ReturnsVersionString)
{
  static const std::string EXPECTED_VERSION_STRING = "Test Version String";

  expect_call_all();
  EXPECT_CALL(*api_, get_version_string())
    .Times(1)
    .WillOnce(Return(EXPECTED_VERSION_STRING.c_str()));

  auto window_manager = make_window_manager();
  EXPECT_EQ(window_manager->version(), EXPECTED_VERSION_STRING);
}

/**
 * Verify that the window manager returns the API's clock time.
 */
TEST_F(GLFWWindowManager, ReturnsTime)
{
  static const double EXPECTED_TIME = 40.0;

  expect_call_all();
  EXPECT_CALL(*api_, get_time())
    .Times(1)
    .WillOnce(Return(EXPECTED_TIME));

  auto window_manager = make_window_manager();
  EXPECT_EQ(window_manager->time(), EXPECTED_TIME);
}

/**
 * Verify that the window manager polls events from the API.
 */
TEST_F(GLFWWindowManager, PollsEvents)
{
  expect_call_all();
  EXPECT_CALL(*api_, poll_events())
    .Times(1);

  auto window_manager = make_window_manager();
  window_manager->poll_events();
}

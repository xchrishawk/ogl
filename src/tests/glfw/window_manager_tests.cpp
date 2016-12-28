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
  auto make_window_manager(const std::shared_ptr<api>& api)
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

  /** Expects that the entire API lifecycle will occur. */
  inline void expect_lifecycle(const std::shared_ptr<glfw::mock::api>& api)
  {
    expect_set_error_callback(api);
    expect_init(api);
    expect_terminate(api);
  }

}

/* -- GLFWWindowManagerInitialization -- */

/**
 * Unit test checking initialization of the `glfw::window_manager` class.
 */
class GLFWWindowManagerInitialization : public Test
{
};

/**
 * Verify that a `std::invalid_argument` exception is thrown if the API object is null.
 */
TEST_F(GLFWWindowManagerInitialization, ExceptionThrownOnInitializationIfAPIIsNull)
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
TEST_F(GLFWWindowManagerInitialization, ExceptionThrownOnInitializationIfGLFWFailsToInitialize)
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
TEST_F(GLFWWindowManagerInitialization, ExceptionThrownOnInitializationIfGLFWIsAlreadyInitialized)
{
  auto api = mock::api::create();
  expect_lifecycle(api);

  try
  {
    auto window_manager = make_window_manager(api);
    auto duplicate_window_manager = make_window_manager(api);
    ADD_FAILURE();
  }
  catch (const ogl::duplicate_object_exception&)
  {
    SUCCEED();
  }
}

/**
 * Verify that a new window manager can be initialized if the previous window manager has been
 * deinitialized.
 */
TEST_F(GLFWWindowManagerInitialization, ReinitializesAfterDeinitializing)
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
  catch (const ogl::duplicate_object_exception&)
  {
    ADD_FAILURE();
  }
}

/**
 * Verify that the static `is_initialized()` method returns `true` if the window manager has already
 * been initialized.
 */
TEST_F(GLFWWindowManagerInitialization, ReturnsIsInitialized)
{
  EXPECT_EQ(window_manager::is_initialized(), false);

  auto api = mock::api::create();
  expect_lifecycle(api);

  // scope
  {
    auto window_manager = make_window_manager(api);
    EXPECT_EQ(window_manager::is_initialized(), true);
  }

  EXPECT_EQ(window_manager::is_initialized(), false);
}

/* -- GLFWWindowManagerOperation -- */

/**
 * Unit test checking the basic operation of the `glfw::window_manager` class against a mock API.
 */
class GLFWWindowManagerOperation : public Test
{
protected:

  std::shared_ptr<mock::api> api_;

  virtual void SetUp() override
  {
    api_ = mock::api::create();
    expect_lifecycle(api_);
  }

  std::shared_ptr<window_manager> make_window_manager()
  { return ::make_window_manager(api_); }

};

/**
 * Verify that the window manager returns the API's version string.
 */
TEST_F(GLFWWindowManagerOperation, ReturnsVersionString)
{
  static const std::string EXPECTED_VERSION_STRING = "Test Version String";

  EXPECT_CALL(*api_, get_version_string())
    .Times(1)
    .WillOnce(Return(EXPECTED_VERSION_STRING.c_str()));

  auto window_manager = make_window_manager();
  EXPECT_EQ(window_manager->version(), EXPECTED_VERSION_STRING);
}

/**
 * Verify that the window manager returns the API's clock time.
 */
TEST_F(GLFWWindowManagerOperation, ReturnsTime)
{
  static const double EXPECTED_TIME = 40.0;

  EXPECT_CALL(*api_, get_time())
    .Times(1)
    .WillOnce(Return(EXPECTED_TIME));

  auto window_manager = make_window_manager();
  EXPECT_EQ(window_manager->time(), EXPECTED_TIME);
}

/**
 * Verify that the window manager polls events from the API.
 */
TEST_F(GLFWWindowManagerOperation, PollsEvents)
{
  EXPECT_CALL(*api_, poll_events())
    .Times(1);

  auto window_manager = make_window_manager();
  window_manager->poll_events();
}

/* -- GLFWWindowManagerIntegration -- */

/**
 * Unit test checking basic interaction with the "live" GLFW library.
 */
class GLFWWindowManagerIntegration : public Test
{
protected:
  static std::shared_ptr<window_manager> window_manager_;
};

// we use a static variable so we only have to init the library once, since it's slow
std::shared_ptr<window_manager> GLFWWindowManagerIntegration::window_manager_ = nullptr;

/**
 * Verify that the GLFW library is successfully initialized.
 */
TEST_F(GLFWWindowManagerIntegration, Initialization)
{
  try
  {
    auto api = api::create();
    window_manager_ = make_window_manager(api);
    EXPECT_EQ(window_manager::is_initialized(), true);
  }
  catch (...)
  {
    // cannot continue
    FAIL();
  }
}

/**
 * Verify that the GLFW library returns a valid time stamp.
 */
TEST_F(GLFWWindowManagerIntegration, ReturnsTime)
{
  // should be < 1 second since window manager was initialized
  EXPECT_GE(window_manager_->time(), 0.0);
  EXPECT_LE(window_manager_->time(), 1.0);
}

/**
 * Verify that the GLFW library is successfully terminated.
 */
TEST_F(GLFWWindowManagerIntegration, Termination)
{
  window_manager_ = nullptr;
  EXPECT_EQ(window_manager::is_initialized(), false);
}

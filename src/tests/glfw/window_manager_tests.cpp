/**
 * @file	window_manager_tests.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <gtest/gtest.h>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "tests/glfw/mock/api.hpp"
#include "util/exceptions.hpp"

/* -- Helper Functions -- */

namespace
{

  /** Create a window manager with the specified API. */
  auto make_window_manager(std::shared_ptr<glfw::mock::api> api)
  {
    glfw::window_manager_args args;
    args.api = api;
    return glfw::window_manager::create(args);
  }

}

/* -- Test Cases -- */

/**
 * Verify that a `std::invalid_argument` exception is thrown if the API object is null.
 */
TEST(GLFWWindowManagerInitialization, ExceptionThrownIfAPIIsNull)
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
 * Verify that an `ogl::duplicate_object_exception` is thrown if the GLFW window
 * manager is initialized while another instance is already active.
 */
TEST(GLFWWindowManagerInitialization, ExceptionThrownIfGLFWIsAlreadyInitialized)
{
  try
  {
    auto api = glfw::mock::api::create();
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
TEST(GLFWWindowManagerInitialization, CanReinitializeAfterDeinitializingPreviousInstance)
{
  try
  {
    auto api = glfw::mock::api::create();
    // for scope
    {
      auto window_manager = make_window_manager(api);
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
 * Verify that an `ogl::library_init_exception` is thrown if initializing GLFW fails.
 */
TEST(GLFWWindowManagerInitialization, ExceptionThrownIfLibraryInitializationFails)
{
  try
  {
    auto api = glfw::mock::api::create();
    api->init_lambda = [] { return 0; };
    auto window_manager = make_window_manager(api);
    ADD_FAILURE();
  }
  catch (ogl::library_init_exception&)
  {
    SUCCEED();
  }
}

/**
 * Verify that the correct version string is returned.
 */
TEST(GLFWWindowManagerOperation, VersionStringReturnsCorrectValue)
{
  static const std::string VERSION("This Is A Test");
  auto api = glfw::mock::api::create();
  api->get_version_string_lambda = [] { return VERSION.c_str(); };
  auto window_manager = make_window_manager(api);
  EXPECT_EQ(window_manager->version(), VERSION);
}

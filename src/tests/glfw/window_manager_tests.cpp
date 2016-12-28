/**
 * @file	window_manager_tests.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "util/exceptions.hpp"

/* -- Test Cases -- */

/**
 * Verify that a `std::invalid_argument` exception is thrown if the API object
 * is null.
 */
TEST(GLFWWindowManagerInitialization, ExceptionThrownIfAPIIsNull)
{
  try
  {
    glfw::window_manager_args args;
    args.api = glfw::api::ptr(nullptr);
    auto window_manager = glfw::window_manager::create(args);
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
  glfw::window_manager_args args;
  auto window_manager = glfw::window_manager::create(args);

  try
  {
    auto duplicate_window_manager = glfw::window_manager::create(args);
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
  glfw::window_manager_args args;

  try
  {
    // for scope
    {
      auto window_manager = glfw::window_manager::create(args);
    }

    auto second_window_manager = glfw::window_manager::create(args);
    SUCCEED();
  }
  catch (ogl::duplicate_object_exception&)
  {
    ADD_FAILURE();
  }
}

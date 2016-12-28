/**
 * @file	window_manager_tests.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <gtest/gtest.h>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "util/exceptions.hpp"

/* -- Test Cases -- */

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

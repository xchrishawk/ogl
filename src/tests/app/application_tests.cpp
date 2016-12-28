/**
 * @file	application_tests.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <gtest/gtest.h>

#include "app/application.hpp"
#include "app/window_manager.hpp"

/* -- Test Cases -- */

/**
 * Verify that an exception is thrown if the window manager is null.
 */
TEST(ApplicationInitialization, ExceptionThrownIfWindowManagerIsNull)
{
  try
  {
    ogl::application_args args;
    args.window_manager = nullptr;
    auto app = ogl::application::create(args);
    ADD_FAILURE();
  }
  catch (std::invalid_argument&)
  {
    SUCCEED();
  }
}

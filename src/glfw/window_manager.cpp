/**
 * @file	window_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <memory>
#include <sstream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace glfw;

/* -- Variables -- */

window_manager* window_manager::instance_s = nullptr;
std::shared_ptr<glfw_error> window_manager::last_error_s = nullptr;

/* -- Procedures -- */

window_manager::window_manager(const window_manager_args& args)
  : api_(args.api)
{
  if (!api_)
    throw std::invalid_argument("API can not be null!");

  // verify we don't already have an instance alive
  if (window_manager::instance_s != nullptr)
    throw std::logic_error("Attempted to initialize GLFW when it is already initialized!");

  api_->set_error_callback(window_manager::error_callback);
  if (!api_->init())
    window_manager::throw_last_error();

  window_manager::instance_s = this;
  ogl_dbg_status("GLFW initialized.");
}

window_manager::~window_manager()
{
  api_->terminate();

  // clear instance so we can reinitialize
  window_manager::instance_s = nullptr;
  ogl_dbg_status("GLFW terminated.");
}

std::string window_manager::version() const
{
  return std::string(api_->get_version_string());
}

double window_manager::time() const
{
  return api_->get_time();
}

void window_manager::poll_events() const
{
  api_->poll_events();
}

void window_manager::error_callback(int error, const char* description)
{
  window_manager::last_error_s = std::shared_ptr<glfw_error>(new glfw_error(error, description));

#if defined(OGL_DEBUG)
  std::ostringstream message;
  message << "GLFW error code " << error << ": " << description;
  ogl_dbg_warning(message.str());
#endif
}

void window_manager::throw_last_error()
{
  if (window_manager::last_error_s)
  {
    glfw_error error = *window_manager::last_error_s;
    window_manager::last_error_s = nullptr;
    throw error;
  }
  else
  {
    ogl_assert_fail("Attempting to throw, but there is no error set!");
    throw glfw_error(-1, "Unknown error");
  }
}

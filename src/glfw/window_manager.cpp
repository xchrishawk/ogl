/**
 * @file	window_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "app/window_manager.hpp"
#include "glfw/window_manager.hpp"
#include "util/debug.hpp"
#include "util/exceptions.hpp"

/* -- Namespaces -- */

using namespace glfw;

/* -- Variables -- */

window_manager* window_manager::instance_s = nullptr;

/* -- Procedures -- */

window_manager::window_manager(const window_manager_args& args)
  : api_(args.api)
{
  if (!api_)
    throw std::invalid_argument("API can not be null!");

  // verify we don't already have an instance alive
  if (window_manager::instance_s != nullptr)
    throw ogl::duplicate_object_exception("Attempted to initialize GLFW when it is already initialized!");

  api_->set_error_callback(window_manager::error_callback);
  if (!api_->init())
    throw ogl::library_init_exception("Failed to initialize GLFW!");

  window_manager::instance_s = this;
  ogl_dbg_status("GLFW initialized.", "API Version:\t\t" + version());
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

void window_manager::error_callback(int error, const char* description)
{
#if defined(OGL_DEBUG)
  std::ostringstream message;
  message << "GLFW error code " << error << ": " << description;
  ogl_dbg_warning(message.str());
  ogl_dbg_breakpoint();
#endif
}

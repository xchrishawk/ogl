/**
 * @file	window.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

/* -- Includes -- */

#include "glfw/window.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace glfw;

/* -- Procedures -- */

window::window(const window_args& args)
  : app::window(),
    api_(args.api),
    window_manager_(args.window_manager)
{
  if (!api_)
    throw std::invalid_argument("API may not be null!");
  if (!window_manager_)
    throw std::invalid_argument("Window manager may not be null!");

  handle_ = api_->create_window(800,
                                600,
                                "Title",
                                nullptr,
                                nullptr);
  if (!handle_)
    window_manager_->throw_last_error();

  ogl_dbg_status("GLFW window created.");
}

window::~window()
{
  api_->destroy_window(handle_);
  ogl_dbg_status("GLFW window destroyed.");
}

bool window::is_current_context() const
{
  const GLFWwindow* const current_context = api_->get_current_context();
  return (current_context == handle_);
}

void window::make_current_context()
{
  api_->make_context_current(handle_);
}

void window::swap_buffers()
{
  api_->swap_buffers(handle_);
}

bool window::should_close() const
{
  return static_cast<bool>(api_->window_should_close(handle_));
}

void window::set_should_close(bool should_close)
{
  api_->set_window_should_close(handle_, static_cast<int>(should_close));
}

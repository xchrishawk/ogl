/**
 * @file	opengl.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <sstream>
#include <stdexcept>

#include "opengl/api.hpp"
#include "opengl/error.hpp"
#include "opengl/opengl.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{

  static const std::vector<std::string> REQUIRED_OPENGL_EXTENSIONS =
  {
    "GL_ARB_direct_state_access",
  };

}

/* -- Variables -- */

opengl* opengl::s_instance = nullptr;

/* -- Procedures -- */

opengl::opengl()
{
  if (opengl::s_instance)
  {
    ogl_dbg_error("Attempted to initialize OpenGL while it was already initialized!");
    ogl::fail();
  }

  // initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW!");

  // there is a bug where GLEW triggers an error on init. flush it from the queue.
  // http://stackoverflow.com/q/20034615/434245
  GLenum error __attribute__((unused)) = ogl::opengl_last_error();
  ogl_dbg_assert(error == GL_INVALID_ENUM);

  opengl::s_instance = this;
  ogl_dbg_status("OpenGL initialized.",
		 "API Version:        " + version(),
		 "GLSL Version:       " + glsl_version(),
		 "Vendor:             " + vendor(),
		 "Renderer:           " + renderer());

  check_required_extensions();
}

opengl::~opengl()
{
  opengl::s_instance = nullptr;
  ogl_dbg_status("OpenGL terminated.");
}

std::string opengl::version() const
{
  return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

std::string opengl::glsl_version() const
{
  return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

std::string opengl::vendor() const
{
  return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

std::string opengl::renderer() const
{
  return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

void opengl::check_required_extensions() const
{
  // build list of unsupported extensions
  std::vector<std::string> unsupported_extensions;
  for (const std::string& extension : REQUIRED_OPENGL_EXTENSIONS)
  {
    if (!glewIsSupported(extension.c_str()))
      unsupported_extensions.push_back(extension);
  }

  // if list isn't empty, throw
  if (!unsupported_extensions.empty())
  {
    std::ostringstream message;
    message << "Unable to initialize OpenGL. Required extensions are not supported:";
    for (const std::string& extension : unsupported_extensions)
      message << " " << extension;
    throw std::runtime_error(message.str());
  }
}

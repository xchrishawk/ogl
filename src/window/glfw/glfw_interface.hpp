/**
 * @file	glfw_interface.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <string>
#include <GLFW/glfw3.h>

#include "window/window_manager.hpp"

/* -- Types -- */

namespace ogl
{
  namespace glfw
  {

    /**
     * Struct containing arguments required to create a `glfw_interface` instance.
     */
    struct glfw_interface_args final
    {
      int opengl_profile;			/**< OpenGL profile version. */
      int opengl_forward_compat;		/**< Should use forward compatibility API? */
      int opengl_context_version_major;		/**< OpenGL context major version. */
      int opengl_context_version_minor;		/**< OpenGL conetxt minor version. */
      int opengl_msaa_samples;			/**< MSAA samples to use. */
    };

    /**
     * Interface class wrapping the GLFW library.
     */
    class glfw_interface final : public window_manager
    {
    public:

      /** Creates a new GLFW interface instance. */
      static ogl::window_manager::ptr create(const glfw_interface_args& args);

      ~glfw_interface();

      /** Returns the GLFW version string. */
      std::string version() const;

      /* -- window_manager -- */

      double time() const;
      void poll_events() const;

    private:

      static glfw_interface* s_instance;

      static void error_callback(int error, const char* description);

      glfw_interface(const glfw_interface_args& args);

    };

  }
}

/* -- Procedures -- */

namespace ogl
{
  namespace glfw
  {

    /** Converts an `int` to a `bool` for the GLFW interface. */
    inline bool glfw_boolean_to_bool(int value)
    {
      return (value != GL_FALSE);
    }

    /** Converts an `bool` to an `int` for the GLFW interface. */
    inline int bool_to_glfw_boolean(bool value)
    {
      return (value ? GL_TRUE : GL_FALSE);
    }

  }
}

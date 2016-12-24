/**
 * @file	glfw_interface.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <string>
#include "window/window_manager.hpp"

/* -- Types -- */

namespace ogl
{
  namespace glfw
  {

    /**
     * Interface class wrapping the GLFW library.
     */
    class glfw_interface : public window_manager
    {
    public:

      /** Creates a new GLFW interface instance. */
      static ogl::window_manager::ptr create();

      ~glfw_interface();

      /** Returns the GLFW version string. */
      std::string version() const;

      /** Returns the current elapsed time, in seconds. */
      double time() const;

      /** Polls for events. */
      void poll_events() const;

    private:

      static glfw_interface* s_instance;

      static void error_callback(int error, const char* description);

      glfw_interface();

    };

  }
}

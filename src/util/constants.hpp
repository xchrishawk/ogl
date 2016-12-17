/**
 * @file	constants.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <string>
#include <GLFW/glfw3.h>

/* -- Constants -- */

namespace ogl
{
  namespace constants
  {

    const double TARGET_INPUT_DELTA_T		= (1.0 / 60.0);
    const double TARGET_STATE_DELTA_T		= (1.0 / 60.0);
    const double TARGET_RENDER_DELTA_T		= (1.0 / 60.0);

    const int WINDOW_INITIAL_WIDTH		= 800;
    const int WINDOW_INITIAL_HEIGHT		= 600;
#if defined(OGL_DEBUG)
    const std::string WINDOW_TITLE		= "OGL (Debug Build)";
#else
    const std::string WINDOW_TITLE		= "OGL";
#endif

    const int OPENGL_PROFILE			= GLFW_OPENGL_CORE_PROFILE;
    const int OPENGL_FORWARD_COMPAT		= GLFW_TRUE;
    const int OPENGL_CONTEXT_VERSION_MAJOR	= 3;
    const int OPENGL_CONTEXT_VERSION_MINOR	= 3;
    const int OPENGL_SWAP_INTERVAL		= 1;

  }
}

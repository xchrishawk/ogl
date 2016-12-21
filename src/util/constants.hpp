/**
 * @file	constants.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <cmath>
#include <string>

#include <glm/glm.hpp>

#include "opengl/api.hpp"

/* -- Constants -- */

namespace ogl
{
  namespace constants
  {

    const double DEG_TO_RAD			= (M_PI / 180.0);
    const double RAD_TO_DEG			= (180.0 / M_PI);

    const glm::vec3 VEC3_UNIT_X(1.0f, 0.0f, 0.0f);
    const glm::vec3 VEC3_UNIT_Y(0.0f, 1.0f, 0.0f);
    const glm::vec3 VEC3_UNIT_Z(0.0f, 0.0f, 1.0f);

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
    const int OPENGL_FORWARD_COMPAT		= static_cast<int>(true);
    const int OPENGL_CONTEXT_VERSION_MAJOR	= 3;
    const int OPENGL_CONTEXT_VERSION_MINOR	= 3;
    const int OPENGL_SWAP_INTERVAL		= 1;	// frames to wait before swapping
    const int OPENGL_SAMPLES			= 4;	// MSAA samples

    const GLint OPENGL_INVALID_LOCATION		= -1;

  }
}

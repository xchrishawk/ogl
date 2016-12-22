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

    /* -- Physical Constants -- */

    /** Converts degrees to radians. */
    const float DEG_TO_RAD			= (M_PI / 180.0);

    /** Converts radians to degrees. */
    const float RAD_TO_DEG			= (180.0 / M_PI);

    /* -- Unit Vectors -- */

    /** 3-dimensional unit vector in the X direction. */
    const glm::vec3 VEC3_UNIT_X(1.0f, 0.0f, 0.0f);

    /** 3-dimensional unit vector in the Y direction. */
    const glm::vec3 VEC3_UNIT_Y(0.0f, 1.0f, 0.0f);

    /** 3-dimensional unit vector in the Z direction. */
    const glm::vec3 VEC3_UNIT_Z(0.0f, 0.0f, 1.0f);

    /** 4-dimensional unit vector in the X direction. */
    const glm::vec4 VEC4_UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);

    /** 4-dimensional unit vector in the Y direction. */
    const glm::vec4 VEC4_UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);

    /** 4-dimensional unit vector in the Z direction. */
    const glm::vec4 VEC4_UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);

    /** 4-dimensional unit vector in the W direction. */
    const glm::vec4 VEC4_UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);

    /* -- App Configuration -- */

    /** Target delta-T for updating app state, in seconds. */
    const float TARGET_STATE_DELTA_T		= (1.0 / 60.0);

    /** Target delta-T for rendering, in seconds. */
    const float TARGET_RENDER_DELTA_T		= (1.0 / 60.0);

    /** Initial width of the app window. */
    const int WINDOW_INITIAL_WIDTH		= 800;

    /** Initial height of the app window. */
    const int WINDOW_INITIAL_HEIGHT		= 600;
#if defined(OGL_DEBUG)

    /** The window title for debug builds. */
    const std::string WINDOW_TITLE		= "OGL (Debug Build)";

#else

    /** The window title for release builds. */
    const std::string WINDOW_TITLE		= "OGL";

#endif

    /* -- OpenGL Configuration -- */

    /** Target OpenGL profile. */
    const int OPENGL_PROFILE			= GLFW_OPENGL_CORE_PROFILE;

    /** Is OpenGL forward compatibility enabled? */
    const int OPENGL_FORWARD_COMPAT		= static_cast<int>(true);

    /** Major version number for target context. */
    const int OPENGL_CONTEXT_VERSION_MAJOR	= 3;

    /** Minor version number for target context. */
    const int OPENGL_CONTEXT_VERSION_MINOR	= 3;

    /** Frames to wait before swapping buffers. */
    const int OPENGL_SWAP_INTERVAL		= 1;

    /** Number of MSAA samples to take. */
    const int OPENGL_SAMPLES			= 4;

    /* -- Misc -- */

    /** Value returned when a vertex attribute or uniform cannot be found in a shader program. */
    const GLint OPENGL_INVALID_LOCATION		= -1;

  }
}

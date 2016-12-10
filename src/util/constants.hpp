/**
 * constants.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_UTIL_CONSTANTS_HPP
#define OGL_UTIL_CONSTANTS_HPP

/* -- Includes -- */

#include <cmath>
#include <glm/glm.hpp>

/* -- Constants -- */

namespace ogl
{

  /** Conversion factor from degrees to radians. */
  const float DEG_TO_RAD = (M_PI / 180.0f);

  /** Conversion factor from radians to degrees. */
  const float RAD_TO_DEG = (1.0f / DEG_TO_RAD);

  const glm::vec3 VEC3_UNIT_X(1.0f, 0.0f, 0.0f);
  const glm::vec3 VEC3_UNIT_Y(0.0f, 1.0f, 0.0f);
  const glm::vec3 VEC3_UNIT_Z(0.0f, 0.0f, 1.0f);

}

/* -- Procedures -- */

namespace ogl
{

  /** Convert degrees to radians. */
  inline float deg_to_rad(float value)
  {
    return value * DEG_TO_RAD;
  }

  /** Convert radians to degrees. */
  inline float rad_to_deg(float value)
  {
    return value * RAD_TO_DEG;
  }

}

#endif /* OGL_UTIL_CONSTANTS_HPP */

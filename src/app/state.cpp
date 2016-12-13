/**
 * state.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "app/examples.hpp"
#include "app/input.hpp"
#include "app/state.hpp"
#include "util/constants.hpp"

/* -- Namespaces -- */

using namespace glm;
using namespace ogl;

/* -- Constants -- */

namespace
{
  const vec3 CAMERA_POS_DEFAULT(0.0f, 0.0f, 5.0f);
  const float CAMERA_POS_PER_SEC = 2.5f;

  const quat CAMERA_ROT_DEFAULT(1.0f, 0.0f, 0.0f, 0.0f);
  const float CAMERA_ROT_PER_SEC = 90.0f * DEG_TO_RAD;

  const float CAMERA_FOV_DEFAULT = 45.0f * DEG_TO_RAD;
  const float CAMERA_FOV_PER_SEC = 10.0f * DEG_TO_RAD;
  const float CAMERA_FOV_MINIMUM = 10.0f * DEG_TO_RAD;
  const float CAMERA_FOV_MAXIMUM = 170.0f * DEG_TO_RAD;
}

/* -- Procedures -- */

state::state()
  : m_camera_pos(CAMERA_POS_DEFAULT),
    m_camera_rot(CAMERA_ROT_DEFAULT),
    m_camera_fov(CAMERA_FOV_DEFAULT),
    m_objects()
{
  m_objects.push_back(object(example_meshes::gray_cube()));
  m_objects.push_back(object(example_meshes::gray_cube(),
			     vec3(3.0, 0.0, 0.0),
			     quat(),
			     vec3(0.5, 0.5, 0.5)));
  m_objects.push_back(object(example_meshes::gray_cube(),
			     vec3(-3.0, 0.0, 0.0),
			     quat(),
			     vec3(0.5, 0.5, 0.5)));
}

state::~state()
{
}

void state::update(float abs_t, float delta_t, const input& input)
{
  update_camera_pos(delta_t, input);
  update_camera_rot(delta_t, input);
  update_camera_fov(delta_t, input);
}

void state::update_camera_pos(float delta_t, const input& input)
{
  // reset
  if (input.input_active(INPUT_KEY_CAMERA_RESET))
  {
    m_camera_rot = CAMERA_ROT_DEFAULT;
    return;
  }

  const float POSITIVE_RATE = CAMERA_ROT_PER_SEC * delta_t;
  const float NEGATIVE_RATE = -POSITIVE_RATE;

  // pitch
  if (input.input_active(INPUT_KEY_CAMERA_PITCH_UP))
    m_camera_rot = rotate(m_camera_rot, POSITIVE_RATE, VEC3_UNIT_X);
  if (input.input_active(INPUT_KEY_CAMERA_PITCH_DOWN))
    m_camera_rot = rotate(m_camera_rot, NEGATIVE_RATE, VEC3_UNIT_X);

  // roll
  if (input.input_active(INPUT_KEY_CAMERA_YAW_RIGHT))
    m_camera_rot = rotate(m_camera_rot, NEGATIVE_RATE, VEC3_UNIT_Y);
  if (input.input_active(INPUT_KEY_CAMERA_YAW_LEFT))
    m_camera_rot = rotate(m_camera_rot, POSITIVE_RATE, VEC3_UNIT_Y);

  // yaw
  if (input.input_active(INPUT_KEY_CAMERA_ROLL_RIGHT))
    m_camera_rot = rotate(m_camera_rot, NEGATIVE_RATE, VEC3_UNIT_Z);
  if (input.input_active(INPUT_KEY_CAMERA_ROLL_LEFT))
    m_camera_rot = rotate(m_camera_rot, POSITIVE_RATE, VEC3_UNIT_Z);
}

void state::update_camera_rot(float delta_t, const input& input)
{
  // reset
  if (input.input_active(INPUT_KEY_CAMERA_RESET))
  {
    m_camera_pos = CAMERA_POS_DEFAULT;
    return;
  }

  const float RATE = CAMERA_POS_PER_SEC * delta_t;
  vec3 translation;

  // right/left
  if (input.input_active(INPUT_KEY_CAMERA_TRANSLATE_RIGHT))
    translation.x += RATE;
  if (input.input_active(INPUT_KEY_CAMERA_TRANSLATE_LEFT))
    translation.x -= RATE;

  // up/down
  if (input.input_active(INPUT_KEY_CAMERA_TRANSLATE_UP))
    translation.y += RATE;
  if (input.input_active(INPUT_KEY_CAMERA_TRANSLATE_DOWN))
    translation.y -= RATE;

  // forward/backward
  if (input.input_active(INPUT_KEY_CAMERA_TRANSLATE_FORWARD))
    translation.z -= RATE;
  if (input.input_active(INPUT_KEY_CAMERA_TRANSLATE_BACKWARD))
    translation.z += RATE;

  // rotate to our local reference frame and add to position
  m_camera_pos += mat3_cast(m_camera_rot) * translation;
}

void state::update_camera_fov(float delta_t, const input& input)
{
  // reset
  if (input.input_active(INPUT_KEY_CAMERA_RESET))
  {
    m_camera_fov = CAMERA_FOV_DEFAULT;
    return;
  }

  const float RATE = CAMERA_FOV_PER_SEC * delta_t;
  if (input.input_active(INPUT_KEY_CAMERA_FOV_INCREASE))
    m_camera_fov += RATE;
  if (input.input_active(INPUT_KEY_CAMERA_FOV_DECREASE))
    m_camera_fov -= RATE;

  if (m_camera_fov < CAMERA_FOV_MINIMUM)
    m_camera_fov = CAMERA_FOV_MINIMUM;
  if (m_camera_fov > CAMERA_FOV_MAXIMUM)
    m_camera_fov = CAMERA_FOV_MAXIMUM;
}

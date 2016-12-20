/**
 * @file	state.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include "app/input.hpp"
#include "app/object_factory.hpp"
#include "app/state.hpp"
#include "scene/scene.hpp"
#include "util/constants.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  const glm::vec3 CAMERA_POSITION_DEFAULT(0.0f, 0.0f, 5.0f);
  const float CAMERA_POSITION_PER_SEC = 2.5f;

  const glm::quat CAMERA_ROTATION_DEFAULT(1.0f, 0.0f, 0.0f, 0.0f);
  const float CAMERA_ROTATION_PER_SEC = 90.0f * constants::DEG_TO_RAD;

  const float CAMERA_FOV_DEFAULT = 45.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_PER_SEC = 10.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_MINIMUM = 10.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_MAXIMUM = 170.0f * constants::DEG_TO_RAD;
}

/* -- Procedures -- */

state::state()
  : m_camera_position(CAMERA_POSITION_DEFAULT),
    m_camera_rotation(CAMERA_ROTATION_DEFAULT),
    m_camera_fov(CAMERA_FOV_DEFAULT),
    m_scene()
{
  // TEMP
  ogl::component ground_component;
  ground_component.set_meshes({ object_factory::plane() });
  ground_component.set_scale({ 500.0f, 500.0f, 0.0f });
  ground_component.set_color({ 0.25f, 0.25f, 0.15f, 1.0f });

  ogl::object ground_object;
  ground_object.set_components({ ground_component });

  ogl::component pyramid_component;
  pyramid_component.set_meshes({ object_factory::pyramid() });
  pyramid_component.set_color({ 0.75f, 0.75f, 0.75f, 1.0f });

  ogl::object pyramid_object;
  pyramid_object.set_components({ pyramid_component });

  ogl::directional_light dir_light;
  dir_light.set_direction({ 1.0f, 0.5f, -0.25f });
  dir_light.set_light({ 1.0f, 1.0f, 1.0f });

  m_scene.set_objects({ ground_object, pyramid_object });
  m_scene.set_directional_lights({ dir_light });
}

void state::run(const state_args& args)
{
  update_camera_position(args);
  update_camera_rotation(args);
  update_camera_fov(args);
}

void state::update_camera_position(const state_args& args)
{
  // reset
  if (args.input.input_active(INPUT_KEY_CAMERA_RESET))
  {
    m_camera_rotation = CAMERA_ROTATION_DEFAULT;
    return;
  }

  const float POSITIVE_RATE = CAMERA_ROTATION_PER_SEC * args.delta_t;
  const float NEGATIVE_RATE = -POSITIVE_RATE;

  // pitch
  if (args.input.input_active(INPUT_KEY_CAMERA_PITCH_UP))
    m_camera_rotation = rotate(m_camera_rotation, POSITIVE_RATE, constants::VEC3_UNIT_X);
  if (args.input.input_active(INPUT_KEY_CAMERA_PITCH_DOWN))
    m_camera_rotation = rotate(m_camera_rotation, NEGATIVE_RATE, constants::VEC3_UNIT_X);

  // roll
  if (args.input.input_active(INPUT_KEY_CAMERA_YAW_RIGHT))
    m_camera_rotation = rotate(m_camera_rotation, NEGATIVE_RATE, constants::VEC3_UNIT_Y);
  if (args.input.input_active(INPUT_KEY_CAMERA_YAW_LEFT))
    m_camera_rotation = rotate(m_camera_rotation, POSITIVE_RATE, constants::VEC3_UNIT_Y);

  // yaw
  if (args.input.input_active(INPUT_KEY_CAMERA_ROLL_RIGHT))
    m_camera_rotation = rotate(m_camera_rotation, NEGATIVE_RATE, constants::VEC3_UNIT_Z);
  if (args.input.input_active(INPUT_KEY_CAMERA_ROLL_LEFT))
    m_camera_rotation = rotate(m_camera_rotation, POSITIVE_RATE, constants::VEC3_UNIT_Z);
}

void state::update_camera_rotation(const state_args& args)
{
  // reset
  if (args.input.input_active(INPUT_KEY_CAMERA_RESET))
  {
    m_camera_position = CAMERA_POSITION_DEFAULT;
    return;
  }

  const float RATE = CAMERA_POSITION_PER_SEC * args.delta_t;
  glm::vec3 translation;

  // right/left
  if (args.input.input_active(INPUT_KEY_CAMERA_TRANSLATE_RIGHT))
    translation.x += RATE;
  if (args.input.input_active(INPUT_KEY_CAMERA_TRANSLATE_LEFT))
    translation.x -= RATE;

  // up/down
  if (args.input.input_active(INPUT_KEY_CAMERA_TRANSLATE_UP))
    translation.y += RATE;
  if (args.input.input_active(INPUT_KEY_CAMERA_TRANSLATE_DOWN))
    translation.y -= RATE;

  // forward/backward
  if (args.input.input_active(INPUT_KEY_CAMERA_TRANSLATE_FORWARD))
    translation.z -= RATE;
  if (args.input.input_active(INPUT_KEY_CAMERA_TRANSLATE_BACKWARD))
    translation.z += RATE;

  // rotate to our local reference frame and add to position
  m_camera_position += mat3_cast(m_camera_rotation) * translation;
}

void state::update_camera_fov(const state_args& args)
{
  // reset
  if (args.input.input_active(INPUT_KEY_CAMERA_RESET))
  {
    m_camera_fov = CAMERA_FOV_DEFAULT;
    return;
  }

  const float RATE = CAMERA_FOV_PER_SEC * args.delta_t;
  if (args.input.input_active(INPUT_KEY_CAMERA_FOV_INCREASE))
    m_camera_fov += RATE;
  if (args.input.input_active(INPUT_KEY_CAMERA_FOV_DECREASE))
    m_camera_fov -= RATE;

  if (m_camera_fov < CAMERA_FOV_MINIMUM)
    m_camera_fov = CAMERA_FOV_MINIMUM;
  if (m_camera_fov > CAMERA_FOV_MAXIMUM)
    m_camera_fov = CAMERA_FOV_MAXIMUM;
}

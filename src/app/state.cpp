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
  component cube_component_1;
  cube_component_1.set_meshes({ object_factory::cone(24) });
  cube_component_1.set_color({ 1.0f, 1.0f, 1.0f, 1.0f });
  cube_component_1.set_scale({ 2.0f, 2.0f, 2.0f });

  component cube_component_2;
  cube_component_2.set_meshes({ object_factory::cube() });
  cube_component_2.set_color({ 1.0f, 0.0f, 0.0f, 1.0f });
  cube_component_2.set_scale({ 0.5f, 0.5f, 0.5f });
  cube_component_2.set_position({ 3.0f, 0.0f, 0.0f });

  component cube_component_3;
  cube_component_3.set_meshes({ object_factory::cube() });
  cube_component_3.set_color({ 0.0f, 1.0f, 0.0f, 1.0f });
  cube_component_3.set_scale({ 0.5f, 0.5f, 0.5f });
  cube_component_3.set_position({ -3.0f, 0.0f, 0.0f });

  component cube_component_4;
  cube_component_4.set_meshes({ object_factory::cube() });
  cube_component_4.set_color({ 0.0f, 0.0f, 1.0f, 1.0f });
  cube_component_4.set_scale({ 0.5f, 0.5f, 0.5f });
  cube_component_4.set_position({ 0.0f, 0.0f, 3.0f });

  component cube_component_5;
  cube_component_5.set_meshes({ object_factory::cube() });
  cube_component_5.set_color({ 0.0f, 1.0f, 1.0f, 1.0f });
  cube_component_5.set_scale({ 0.5f, 0.5f, 0.5f });
  cube_component_5.set_position({ 0.0f, 0.0f, -3.0f });

  component cube_component_6;
  cube_component_6.set_meshes({ object_factory::cube() });
  cube_component_6.set_color({ 1.0f, 0.0f, 1.0f, 1.0f });
  cube_component_6.set_scale({ 0.5f, 0.5f, 0.5f });
  cube_component_6.set_position({ 0.0f, 3.0f, 0.0f });

  component cube_component_7;
  cube_component_7.set_meshes({ object_factory::cube() });
  cube_component_7.set_color({ 1.0f, 1.0f, 0.0f, 1.0f });
  cube_component_7.set_scale({ 0.5f, 0.5f, 0.5f });
  cube_component_7.set_position({ 0.0f, -3.0f, 0.0f });

  object cube_object;
  cube_object.set_components({
      cube_component_1,
	cube_component_2,
	cube_component_3,
	cube_component_4,
	cube_component_5,
	cube_component_6,
	cube_component_7 });

  m_scene.set_objects({ cube_object });
  m_scene.set_ambient_light({ 0.1f, 0.1f, 0.1f });
  m_scene.set_directional_light({ 0.8f, 0.8f, 0.8f });
}

void state::run(const state_args& args)
{
  update_camera_position(args);
  update_camera_rotation(args);
  update_camera_fov(args);

  m_scene.set_directional_light_direction({ cos(args.abs_t), sin(args.abs_t), 0.0f });
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

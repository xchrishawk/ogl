/**
 * @file	state_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include "app/input_manager.hpp"
#include "app/state_manager.hpp"
#include "app/wavefront_file.hpp"
#include "scene/component.hpp"
#include "scene/object.hpp"
#include "scene/scene.hpp"
#include "util/constants.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  const glm::vec3 CAMERA_POSITION_DEFAULT(0.0f, 0.0f, 10.0f);
  const float CAMERA_POSITION_PER_SEC = 2.5f;

  const glm::quat CAMERA_ROTATION_DEFAULT(1.0f, 0.0f, 0.0f, 0.0f);
  const float CAMERA_ROTATION_PER_SEC = 90.0f * constants::DEG_TO_RAD;

  const float CAMERA_FOV_DEFAULT = 45.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_PER_SEC = 10.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_MINIMUM = 10.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_MAXIMUM = 170.0f * constants::DEG_TO_RAD;
}

/* -- Procedures -- */

state_manager::state_manager()
  : m_scene()
{
  // TEMP
  wavefront_file cow("/home/chris/teapot.obj");

  component comp;
  comp.set_meshes({ cow.to_mesh() });
  comp.set_color({ 1.0f, 1.0f, 1.0f, 1.0f });

  object obj;
  obj.set_components({ comp });

  m_scene.set_objects({ obj });
  m_scene.set_ambient_light({ 0.1f, 0.1f, 0.1f });
  m_scene.set_directional_light({ 0.1f, 0.1f, 1.0f });
  m_scene.set_directional_light_direction({ -1.0f, -1.0f, -1.0f });
  default_camera();
}

void state_manager::run(const state_loop_args& args)
{
  update_camera(args);
}

void state_manager::input_key_pressed(input_key input)
{
  switch (input)
  {
  case INPUT_KEY_CAMERA_RESET:
    default_camera();
    break;

  default:
    break;
  }
}

void state_manager::default_camera()
{
  m_scene.set_camera_position(CAMERA_POSITION_DEFAULT);
  m_scene.set_camera_rotation(CAMERA_ROTATION_DEFAULT);
  m_scene.set_camera_fov(CAMERA_FOV_DEFAULT);
}

void state_manager::update_camera(const state_loop_args& args)
{
  update_camera_position(args);
  update_camera_rotation(args);
  update_camera_fov(args);
}

void state_manager::update_camera_position(const state_loop_args& args)
{
  const float RATE = CAMERA_POSITION_PER_SEC * args.delta_t;
  glm::vec3 translation;

  // forward/backward
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_FORWARD))
    translation.z -= RATE;
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_BACKWARD))
    translation.z += RATE;

  // right/left
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_RIGHT))
    translation.x += RATE;
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_LEFT))
    translation.x -= RATE;

  // up/down
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_UP))
    translation.y += RATE;
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_DOWN))
    translation.y -= RATE;

  // rotate to our local reference frame and add to position
  glm::vec3 camera_position = m_scene.camera_position();
  camera_position += mat3_cast(m_scene.camera_rotation()) * translation;
  m_scene.set_camera_position(camera_position);
}

void state_manager::update_camera_rotation(const state_loop_args& args)
{
  const float POSITIVE_RATE = CAMERA_ROTATION_PER_SEC * args.delta_t;
  const float NEGATIVE_RATE = -POSITIVE_RATE;

  glm::quat camera_rotation = m_scene.camera_rotation();

  // pitch
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_PITCH_UP))
    camera_rotation = rotate(camera_rotation, POSITIVE_RATE, constants::VEC3_UNIT_X);
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_PITCH_DOWN))
    camera_rotation = rotate(camera_rotation, NEGATIVE_RATE, constants::VEC3_UNIT_X);

  // roll
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_YAW_RIGHT))
    camera_rotation = rotate(camera_rotation, NEGATIVE_RATE, constants::VEC3_UNIT_Y);
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_YAW_LEFT))
    camera_rotation = rotate(camera_rotation, POSITIVE_RATE, constants::VEC3_UNIT_Y);

  // yaw
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_ROLL_RIGHT))
    camera_rotation = rotate(camera_rotation, NEGATIVE_RATE, constants::VEC3_UNIT_Z);
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_ROLL_LEFT))
    camera_rotation = rotate(camera_rotation, POSITIVE_RATE, constants::VEC3_UNIT_Z);

  m_scene.set_camera_rotation(camera_rotation);
}

void state_manager::update_camera_fov(const state_loop_args& args)
{
  const float RATE = CAMERA_FOV_PER_SEC * args.delta_t;
  float camera_fov = m_scene.camera_fov();

  if (args.input_manager.input_key_state(INPUT_KEY_SCALE_DOWN))
    camera_fov += RATE;
  if (args.input_manager.input_key_state(INPUT_KEY_SCALE_UP))
    camera_fov -= RATE;

  if (camera_fov < CAMERA_FOV_MINIMUM)
    camera_fov = CAMERA_FOV_MINIMUM;
  if (camera_fov > CAMERA_FOV_MAXIMUM)
    camera_fov = CAMERA_FOV_MAXIMUM;

  m_scene.set_camera_fov(camera_fov);
}

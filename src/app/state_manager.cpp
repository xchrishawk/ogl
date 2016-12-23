/**
 * @file	state_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include <climits>
#include <sstream>

#include "app/input_manager.hpp"
#include "app/state_manager.hpp"
#include "app/wavefront_file.hpp"
#include "scene/component.hpp"
#include "scene/object.hpp"
#include "scene/scene.hpp"
#include "util/constants.hpp"
#include "util/debug.hpp"
#include "util/misc.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Constants -- */

namespace
{
  const control_mode DEFAULT_CONTROL_MODE = CONTROL_MODE_CAMERA;
  const int DEFAULT_CONTROL_OBJECT_INDEX = 0;

  const glm::vec3 CAMERA_POSITION_DEFAULT(0.0f, 0.0f, 10.0f);
  const float CAMERA_POSITION_PER_SEC = 10.0f;

  const glm::quat CAMERA_ROTATION_DEFAULT(1.0f, 0.0f, 0.0f, 0.0f);
  const float CAMERA_ROTATION_PER_SEC = 90.0f * constants::DEG_TO_RAD;

  const float CAMERA_FOV_DEFAULT = 45.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_PER_SEC = 10.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_MINIMUM = 10.0f * constants::DEG_TO_RAD;
  const float CAMERA_FOV_MAXIMUM = 170.0f * constants::DEG_TO_RAD;

  const float OBJECT_POSITION_PER_SEC = 2.5f;
  const float OBJECT_ROTATION_PER_SEC = 90.0f * constants::DEG_TO_RAD;
  const float OBJECT_SCALE_PER_SEC = 0.5f;
  const float OBJECT_SCALE_MINIMUM = 0.0f;
  const float OBJECT_SCALE_MAXIMUM = FLT_MAX;
}

/* -- Procedures -- */

state_manager::state_manager()
  : m_control_mode(DEFAULT_CONTROL_MODE),
    m_control_object_index(DEFAULT_CONTROL_OBJECT_INDEX),
    m_scene()
{
  wavefront_file teapot_file("/home/chris/teapot.obj");
  component teapot_component;
  teapot_component.set_meshes({ teapot_file.to_mesh() });
  teapot_component.set_color({ 1.0f, 0.0f, 0.0f, 1.0f });
  object teapot_object;
  teapot_object.set_components({ teapot_component });

  wavefront_file cow_file("/home/chris/cow-nonormals.obj");
  component cow_component;
  cow_component.set_meshes({ cow_file.to_mesh() });
  cow_component.set_color({ 0.0f, 1.0f, 0.0f, 1.0f });
  object cow_object;
  cow_object.set_components({ cow_component });

  m_scene.set_objects({ teapot_object, cow_object });
  m_scene.set_ambient_light({ 0.1f, 0.1f, 0.1f });
  m_scene.set_directional_light({ 1.0f, 1.0f, 1.0f });
  m_scene.set_directional_light_direction({ -1.0f, -1.0f, -1.0f });
  default_camera();
}

void state_manager::run(const state_loop_args& args)
{
  switch (m_control_mode)
  {
  case CONTROL_MODE_CAMERA:
    update_camera(args);
    break;

  case CONTROL_MODE_OBJECT:
    update_object(args);
    break;

  default:
    break;
  }
}

void state_manager::input_key_pressed(input_key input)
{
  switch (input)
  {
  case INPUT_KEY_CAMERA_RESET:
  {
    default_camera();
    ogl_dbg_status("Reset camera to default.");
    break;
  }

  case INPUT_KEY_CONTROL_MODE_CAMERA:
  {
    m_control_mode = CONTROL_MODE_CAMERA;
    ogl_dbg_status("Control mode is CONTROL_MODE_CAMERA.");
    break;
  }

  case INPUT_KEY_CONTROL_MODE_OBJECT:
  {
    m_control_mode = CONTROL_MODE_OBJECT;
    ogl_dbg_status("Control mode is CONTROL_MODE_OBJECT.");
    break;
  }

  case INPUT_KEY_CONTROL_OBJECT_CYCLE:
  {
    if (m_control_mode != CONTROL_MODE_OBJECT)
      break;

    ++m_control_object_index;
    if (m_control_object_index >= m_scene.object_count())
      m_control_object_index = 0;

#if defined(OGL_DEBUG)
    std::ostringstream message;
    message << "Control object index is " << m_control_object_index << ".";
    ogl_dbg_status(message.str());
#endif
    break;
  }

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
  auto camera_position = translate(m_scene.camera_position(), m_scene.camera_rotation(), CAMERA_POSITION_PER_SEC, args);
  m_scene.set_camera_position(camera_position);
}

void state_manager::update_camera_rotation(const state_loop_args& args)
{
  auto camera_rotation = rotate(m_scene.camera_rotation(), CAMERA_ROTATION_PER_SEC, args);
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

  camera_fov = clamp(camera_fov, CAMERA_FOV_MINIMUM, CAMERA_FOV_MAXIMUM);
  m_scene.set_camera_fov(camera_fov);
}

void state_manager::update_object(const state_loop_args& args)
{
  if (m_control_object_index < 0 || m_control_object_index >= m_scene.object_count())
    return;

  std::vector<object> objs = m_scene.objects();
  object obj = objs[m_control_object_index];

  update_object_position(args, obj);
  update_object_rotation(args, obj);
  update_object_scale(args, obj);

  objs[m_control_object_index] = obj;
  m_scene.set_objects(objs);
}

void state_manager::update_object_position(const state_loop_args& args, object& obj)
{
  auto object_position = translate(obj.position(), obj.rotation(), OBJECT_POSITION_PER_SEC, args);
  obj.set_position(object_position);
}

void state_manager::update_object_rotation(const state_loop_args& args, object& obj)
{
  auto object_rotation = rotate(obj.rotation(), OBJECT_ROTATION_PER_SEC, args);
  obj.set_rotation(object_rotation);
}

void state_manager::update_object_scale(const state_loop_args& args, object& obj)
{
  auto object_scale = scale(obj.scale(), OBJECT_SCALE_PER_SEC, args);
  obj.set_scale(object_scale);
}

glm::vec3 state_manager::translate(const glm::vec3& position,
				   const glm::quat& rotation,
				   float rate,
				   const state_loop_args& args)
{
  const float DELTA = rate * args.delta_t;
  glm::vec3 translation;

  // forward/backward
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_FORWARD))
    translation.z -= DELTA;
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_BACKWARD))
    translation.z += DELTA;

  // right/left
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_RIGHT))
    translation.x += DELTA;
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_LEFT))
    translation.x -= DELTA;

  // up/down
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_UP))
    translation.y += DELTA;
  if (args.input_manager.input_key_state(INPUT_KEY_TRANSLATE_DOWN))
    translation.y -= DELTA;

  // rotate to local reference frame and add to position
  return position + (mat3_cast(rotation) * translation);
}

glm::quat state_manager::rotate(const glm::quat& quat,
				float rate,
				const state_loop_args& args)
{
  const float POSITIVE_DELTA = rate * args.delta_t;
  const float NEGATIVE_DELTA = -POSITIVE_DELTA;
  glm::quat ret = quat;

  // pitch
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_PITCH_UP))
    ret = glm::rotate(ret, POSITIVE_DELTA, constants::VEC3_UNIT_X);
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_PITCH_DOWN))
    ret = glm::rotate(ret, NEGATIVE_DELTA, constants::VEC3_UNIT_X);

  // roll
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_ROLL_RIGHT))
    ret = glm::rotate(ret, NEGATIVE_DELTA, constants::VEC3_UNIT_Z);
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_ROLL_LEFT))
    ret = glm::rotate(ret, POSITIVE_DELTA, constants::VEC3_UNIT_Z);

  // yaw
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_YAW_RIGHT))
    ret = glm::rotate(ret, NEGATIVE_DELTA, constants::VEC3_UNIT_Y);
  if (args.input_manager.input_key_state(INPUT_KEY_ROTATE_YAW_LEFT))
    ret = glm::rotate(ret, POSITIVE_DELTA, constants::VEC3_UNIT_Y);

  return ret;
}

glm::vec3 state_manager::scale(const glm::vec3& scale,
			       float rate,
			       const state_loop_args& args)
{
  const float DELTA = rate * args.delta_t;
  glm::vec3 ret = scale;

  if (args.input_manager.input_key_state(INPUT_KEY_SCALE_DOWN))
  {
    ret.x -= DELTA;
    ret.y -= DELTA;
    ret.z -= DELTA;
  }
  if (args.input_manager.input_key_state(INPUT_KEY_SCALE_UP))
  {
    ret.x += DELTA;
    ret.y += DELTA;
    ret.z += DELTA;
  }

  ret.x = clamp(ret.x, 0.0f, FLT_MAX);
  ret.y = clamp(ret.y, 0.0f, FLT_MAX);
  ret.z = clamp(ret.z, 0.0f, FLT_MAX);

  return ret;
}

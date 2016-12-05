/**
 * state.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cmath>
#include <iostream>
#include <vector>

#include "constants.hpp"
#include "key_input.hpp"
#include "mesh.hpp"
#include "state.hpp"
#include "vertex.hpp"

/* -- Namespaces -- */

using namespace std;
using namespace ogl;

/* -- Constants -- */

namespace
{
  const float CAMERA_POS_PER_SEC = 0.5f;
  const float CAMERA_ROT_PER_SEC = 90.0f * DEG_TO_RAD;
}

/* -- Procedures -- */

state::state()
  : m_camera_pos(0.0f, 0.0f, 3.0f),
    m_camera_rot(0.0f, 0.0f, 0.0f)
{
  static const vertex RGB_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	-0.2f,	-0.2f,	0.0f,	1.0f,	1.0f,	1.0f,	1.0f	},
    {	0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f	},
    {	0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f	},
    {	0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f	},
  };
  static const GLuint RGB_INDICES[] = { 0, 1, 2, 0, 2, 3 };
  m_meshes.push_back(mesh::create(RGB_VERTICES, ogl_array_size(RGB_VERTICES),
				  RGB_INDICES, ogl_array_size(RGB_INDICES)));

  static const vertex CMY_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	0.2f,	0.2f,	0.0f,	1.0f,	1.0f,	1.0f,	1.0f	},
    {	-0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f	},
    {	-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f	},
    {	0.0f,	-0.5f,	0.0f,	1.0f,	0.0f,	1.0f,	1.0f	},
  };
  static const GLuint CMY_INDICES[] = { 0, 1, 2, 0, 2, 3 };
  m_meshes.push_back(mesh::create(CMY_VERTICES, ogl_array_size(CMY_VERTICES),
				  CMY_INDICES, ogl_array_size(CMY_INDICES)));
}

void state::loop(float abs_t, float delta_t, const key_input& key_input)
{
  update_camera_pos(delta_t, key_input);
  update_camera_rot(delta_t, key_input);
}

void state::update_camera_pos(float delta_t, const key_input& key_input)
{
  // right/left
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_RIGHT))
    m_camera_pos.x += CAMERA_POS_PER_SEC * delta_t;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_LEFT))
    m_camera_pos.x -= CAMERA_POS_PER_SEC * delta_t;

  // up/down
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_UP))
    m_camera_pos.y += CAMERA_POS_PER_SEC * delta_t;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_DOWN))
    m_camera_pos.y -= CAMERA_POS_PER_SEC * delta_t;

  // forward/backward
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_FORWARD))
    m_camera_pos.z -= CAMERA_POS_PER_SEC * delta_t;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_BACKWARD))
    m_camera_pos.z += CAMERA_POS_PER_SEC * delta_t;

  // reset
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_RESET))
    m_camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void state::update_camera_rot(float delta_t, const key_input& key_input)
{
  // pitch
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_PITCH_UP))
    m_camera_rot.x += CAMERA_ROT_PER_SEC * delta_t;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_PITCH_DOWN))
    m_camera_rot.x -= CAMERA_ROT_PER_SEC * delta_t;
  m_camera_rot.x = fmodf(m_camera_rot.x, 360.0 * DEG_TO_RAD);

  // roll
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_ROLL_RIGHT))
    m_camera_rot.z += CAMERA_ROT_PER_SEC * delta_t;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_ROLL_LEFT))
    m_camera_rot.z -= CAMERA_ROT_PER_SEC * delta_t;
  m_camera_rot.z = fmodf(m_camera_rot.z, 360.0 * DEG_TO_RAD);

  // yaw
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_YAW_RIGHT))
    m_camera_rot.y -= CAMERA_ROT_PER_SEC * delta_t;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_YAW_LEFT))
    m_camera_rot.y += CAMERA_ROT_PER_SEC * delta_t;
  m_camera_rot.y = fmodf(m_camera_rot.y, 360.0 * DEG_TO_RAD);

  // reset
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_RESET))
    m_camera_rot = glm::vec3(0.0f, 0.0f, 0.0f);
}

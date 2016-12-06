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
  const glm::vec3 DEFAULT_CAMERA_POS(0.0f, 0.0f, 3.0f);
  const glm::quat DEFAULT_CAMERA_ROT(1.0f, 0.0f, 0.0f, 0.0f);

  const float CAMERA_POS_PER_SEC = 1.0f;
  const float CAMERA_ROT_PER_SEC = 90.0f * DEG_TO_RAD;
}

/* -- Procedures -- */

state::state()
  : m_camera_rot(DEFAULT_CAMERA_ROT),
    m_camera_pos(DEFAULT_CAMERA_POS)
{
  static const vertex RGB_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {  	-0.5f,	0.5f, 	0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	},	// 0 - front top left
    { 	0.5f,	0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	1.0f,	},	// 1 - front top right
    {	-0.5f,	-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	},	// 2 - front bottom left
    {	0.5f,	-0.5f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	},	// 3 - front bottom right
    {  	-0.5f,	0.5f, 	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,	},	// 4 - back top left
    { 	0.5f,	0.5f,	-0.5f,	1.0f,	1.0f,	0.0f,	1.0f,	},	// 5 - back top right
    {	-0.5f,	-0.5f,	-0.5f,	0.0f,	1.0f,	1.0f,	1.0f,	},	// 6 - back bottom left
    {	0.5f,	-0.5f,	-0.5f,	1.0f,	0.0f,	1.0f,	1.0f,	},	// 7 - back bottom right

  };
  static const GLuint RGB_INDICES[] =
  {
    0, 1, 2, 1, 2, 3,		// front face
    4, 5, 6, 5, 6, 7,		// back face
    0, 1, 4, 4, 5, 1,		// top face
    2, 3, 6, 6, 7, 3,		// bottom face
    0, 2, 4, 4, 6, 2,		// left face
    1, 3, 5, 5, 7, 3,		// right face
  };
  m_meshes.push_back(mesh::create(RGB_VERTICES, ogl_array_size(RGB_VERTICES),
				  RGB_INDICES, ogl_array_size(RGB_INDICES)));
}

void state::loop(float abs_t, float delta_t, const key_input& key_input)
{
  update_camera_pos(delta_t, key_input);
  update_camera_rot(delta_t, key_input);
}

void state::update_camera_rot(float delta_t, const key_input& key_input)
{
  // reset
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_RESET))
  {
    m_camera_rot = DEFAULT_CAMERA_ROT;
    return;
  }

  const float POSITIVE_RATE = CAMERA_ROT_PER_SEC * delta_t;
  const float NEGATIVE_RATE = -POSITIVE_RATE;

  // pitch
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_PITCH_UP))
    m_camera_rot = glm::rotate(m_camera_rot, POSITIVE_RATE, UNIT_X);
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_PITCH_DOWN))
    m_camera_rot = glm::rotate(m_camera_rot, NEGATIVE_RATE, UNIT_X);

  // roll
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_YAW_RIGHT))
    m_camera_rot = glm::rotate(m_camera_rot, NEGATIVE_RATE, UNIT_Y);
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_YAW_LEFT))
    m_camera_rot = glm::rotate(m_camera_rot, POSITIVE_RATE, UNIT_Y);

  // yaw
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_ROLL_RIGHT))
    m_camera_rot = glm::rotate(m_camera_rot, POSITIVE_RATE, UNIT_Z);
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_ROLL_LEFT))
    m_camera_rot = glm::rotate(m_camera_rot, NEGATIVE_RATE, UNIT_Z);
}

void state::update_camera_pos(float delta_t, const key_input& key_input)
{
  // reset
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_RESET))
  {
    m_camera_pos = DEFAULT_CAMERA_POS;
    return;
  }

  const float RATE = CAMERA_POS_PER_SEC * delta_t;
  glm::vec3 translation;

  // right/left
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_RIGHT))
    translation.x += RATE;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_LEFT))
    translation.x -= RATE;

  // up/down
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_UP))
    translation.y += RATE;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_DOWN))
    translation.y -= RATE;

  // forward/backward
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_FORWARD))
    translation.z -= RATE;
  if (key_input.input_active(KEY_INPUT_TYPE_CAMERA_TRANSLATE_BACKWARD))
    translation.z += RATE;

  // rotate to our local reference frame and add to position
  m_camera_pos += glm::mat3_cast(m_camera_rot) * translation;
}

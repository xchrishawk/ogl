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
  static const float FRONT 	= 0.5f;
  static const float BACK 	= -0.5f;
  static const float RIGHT 	= 0.5f;
  static const float LEFT 	= -0.5f;
  static const float TOP	= 0.5f;
  static const float BOTTOM	= -0.5f;

  static const vertex FRONT_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	LEFT,	TOP,	FRONT,	1.0f,	0.0f,	0.0f,	1.0f	},
    {	RIGHT,	TOP,	FRONT,	1.0f,	0.0f,	0.0f,	1.0f	},
    {	LEFT,	BOTTOM,	FRONT,	1.0f,   0.0f,	0.0f,	1.0f	},
    {	RIGHT,	BOTTOM,	FRONT,	1.0f,	0.0f,	0.0f,	1.0f	},
  };
  static const GLuint FRONT_INDICES[] = { 0, 1, 2, 1, 2, 3 };
  m_meshes.push_back(mesh::create(FRONT_VERTICES, ogl_array_size(FRONT_VERTICES),
				  FRONT_INDICES, ogl_array_size(FRONT_INDICES)));

  static const vertex BACK_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	LEFT,	TOP,	BACK,	1.0f,	1.0f,	0.0f,	1.0f	},
    {	RIGHT,	TOP,	BACK,	1.0f,	1.0f,	0.0f,	1.0f	},
    {	LEFT,	BOTTOM,	BACK,	1.0f,   1.0f,	0.0f,	1.0f	},
    {	RIGHT,	BOTTOM,	BACK,	1.0f,	1.0f,	0.0f,	1.0f	},
  };
  static const GLuint BACK_INDICES[] = { 0, 1, 2, 1, 2, 3 };
  m_meshes.push_back(mesh::create(BACK_VERTICES, ogl_array_size(BACK_VERTICES),
				  BACK_INDICES, ogl_array_size(BACK_INDICES)));

  static const vertex LEFT_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	LEFT,	TOP,	FRONT,	0.0f,	1.0f,	0.0f,	1.0f	},
    {	LEFT,	BOTTOM,	FRONT,	0.0f,	1.0f,	0.0f,	1.0f	},
    {	LEFT,	TOP,	BACK,	0.0f,   1.0f,	0.0f,	1.0f	},
    {	LEFT,	BOTTOM,	BACK,	0.0f,	1.0f,	0.0f,	1.0f	},
  };
  static const GLuint LEFT_INDICES[] = { 0, 1, 2, 1, 2, 3 };
  m_meshes.push_back(mesh::create(LEFT_VERTICES, ogl_array_size(LEFT_VERTICES),
				  LEFT_INDICES, ogl_array_size(LEFT_INDICES)));

  static const vertex RIGHT_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	RIGHT,	TOP,	FRONT,	0.0f,	1.0f,	1.0f,	1.0f	},
    {	RIGHT,	BOTTOM,	FRONT,	0.0f,	1.0f,	1.0f,	1.0f	},
    {	RIGHT,	TOP,	BACK,	0.0f,   1.0f,	1.0f,	1.0f	},
    {	RIGHT,	BOTTOM,	BACK,	0.0f,	1.0f,	1.0f,	1.0f	},
  };
  static const GLuint RIGHT_INDICES[] = { 0, 1, 2, 1, 2, 3 };
  m_meshes.push_back(mesh::create(RIGHT_VERTICES, ogl_array_size(RIGHT_VERTICES),
				  RIGHT_INDICES, ogl_array_size(RIGHT_INDICES)));

  static const vertex TOP_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	LEFT,	TOP,	FRONT,	0.0f,	0.0f,	1.0f,	1.0f	},
    {	RIGHT,	TOP,	FRONT,	0.0f,	0.0f,	1.0f,	1.0f	},
    {	LEFT,	TOP,	BACK,	0.0f,   0.0f,	1.0f,	1.0f	},
    {	RIGHT,	TOP,	BACK,	0.0f,	0.0f,	1.0f,	1.0f	},
  };
  static const GLuint TOP_INDICES[] = { 0, 1, 2, 1, 2, 3 };
  m_meshes.push_back(mesh::create(TOP_VERTICES, ogl_array_size(TOP_VERTICES),
				  TOP_INDICES, ogl_array_size(TOP_INDICES)));

  static const vertex BOTTOM_VERTICES[] =
  {
    //  X	Y	Z	R	G	B	A
    {	LEFT,	BOTTOM,	FRONT,	1.0f,	0.0f,	1.0f,	1.0f	},
    {	RIGHT,	BOTTOM,	FRONT,	1.0f,	0.0f,	1.0f,	1.0f	},
    {	LEFT,	BOTTOM,	BACK,	1.0f,   0.0f,	1.0f,	1.0f	},
    {	RIGHT,	BOTTOM,	BACK,	1.0f,	0.0f,	1.0f,	1.0f	},
  };
  static const GLuint BOTTOM_INDICES[] = { 0, 1, 2, 1, 2, 3 };
  m_meshes.push_back(mesh::create(BOTTOM_VERTICES, ogl_array_size(BOTTOM_VERTICES),
				  BOTTOM_INDICES, ogl_array_size(BOTTOM_INDICES)));
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

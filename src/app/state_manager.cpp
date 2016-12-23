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

/* -- Procedures -- */

state_manager::state_manager()
  : m_scene()
{
  // TEMP
  wavefront_file cow("/home/chris/cow-nonormals.obj");

  component comp;
  comp.set_meshes({ cow.to_mesh() });
  comp.set_color({ 1.0f, 0.0f, 1.0f, 1.0f });

  object obj;
  obj.set_components({ comp });

  m_scene.set_objects({ obj });
  m_scene.set_camera_position({ 0.0f, 0.0f, 10.0f });
  m_scene.set_camera_fov(45.0f * constants::DEG_TO_RAD);
}

void state_manager::run(const state_loop_args& args)
{

}

void state_manager::input_key_pressed(input_key input)
{
}

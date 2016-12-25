/**
 * @file	simple_render_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

// <TEMP>
#include <GL/glew.h>
// </TEMP>

#include "app/render_manager.hpp"
#include "app/render/simple_render_manager.hpp"
#include "app/state/simple_state_manager.hpp"
#include "opengl/opengl.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

render_manager::ptr simple_render_manager::create()
{
  return render_manager::ptr(new simple_render_manager());
}

simple_render_manager::simple_render_manager()
{
}

simple_render_manager::~simple_render_manager()
{
}

void simple_render_manager::run(const render_run_args& args)
{
  // I'm sure there's probably a better way of doing this...
  const simple_state_manager* state_manager
    = dynamic_cast<const simple_state_manager*>(args.state_manager.get());
  ogl_dbg_assert(state_manager != nullptr);

  // <TEMP>
  glClearColor(state_manager->background_color().r,
	       state_manager->background_color().g,
	       state_manager->background_color().b,
	       1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  // </TEMP>
}

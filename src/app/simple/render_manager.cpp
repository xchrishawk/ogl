/**
 * @file	render_manager.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

/* -- Includes -- */

// <TEMP>
#include <GL/glew.h>
// </TEMP>

#include "app/render_manager.hpp"
#include "app/simple/render_manager.hpp"
#include "app/simple/state_manager.hpp"
#include "opengl/opengl.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

render_manager::ptr simple::render_manager::create(const simple::render_manager_args& args)
{
  return render_manager::ptr(new simple::render_manager(args));
}

simple::render_manager::render_manager(const simple::render_manager_args& args)
  : m_resource_manager(args.resource_manager)
{
}

simple::render_manager::~render_manager()
{
}

void simple::render_manager::run(const render_run_args& args)
{
  // I'm sure there's probably a better way of doing this...
  const simple::state_manager* state_manager
    = dynamic_cast<const simple::state_manager*>(args.state_manager.get());
  ogl_dbg_assert(state_manager != nullptr);

  // <TEMP>
  glClearColor(state_manager->background_color().r,
	       state_manager->background_color().g,
	       state_manager->background_color().b,
	       1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  // </TEMP>
}

/**
 * @file	renderer.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include "app/state.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing information required to run a render loop.
   */
  class render_args
  {
  public:

    render_args(const ogl::state& state,
		double abs_t,
		double delta_t,
		int framebuffer_width,
		int framebuffer_height)
      : state(state),
	abs_t(abs_t),
	delta_t(delta_t),
	framebuffer_width(framebuffer_width),
	framebuffer_height(framebuffer_height)
    { }

    const ogl::state& state;
    const double abs_t;
    const double delta_t;
    const int framebuffer_width;
    const int framebuffer_height;

  };

  /**
   * Class responsible for rendering the app's graphics.
   */
  class renderer
  {
  public:

    renderer() { }

    /** Renders a frame to the current OpenGL context. */
    void render(const render_args& args);

  private:

    renderer(const renderer&) = delete;
    renderer& operator =(const renderer&) = delete;

  };

}

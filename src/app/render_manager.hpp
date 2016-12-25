/**
 * @file	render_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include <memory>

#include "app/state_manager.hpp"
#include "opengl/opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing information required to render a frame.
   */
  struct render_run_args
  {
    double abs_t;
    double delta_t;
    ogl::state_manager::const_ptr state_manager;
    ogl::opengl::ptr opengl;
  };

  /**
   * Abstract interface for types managing rendering.
   */
  class render_manager
  {
  public:

    /** Shared pointer to a `render_manager` object. */
    typedef std::shared_ptr<render_manager> ptr;

    /** Shared pointer to a `const render_manager` object. */
    typedef std::shared_ptr<const render_manager> const_ptr;

    virtual ~render_manager() { }

    /**
     * Renders a frame in the current OpenGL context.
     *
     * @param args
     * Arguments object containing information needed to render the frame.
     */
    virtual void run(const render_run_args& args) = 0;

  protected:

    render_manager() { }

  private:

    render_manager(const render_manager&) = delete;
    render_manager& operator =(const render_manager&) = delete;

  };

}

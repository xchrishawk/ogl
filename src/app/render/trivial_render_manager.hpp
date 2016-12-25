/**
 * @file	trivial_render_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include "app/render_manager.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class for performing trivial rendering.
   */
  class trivial_render_manager : public render_manager
  {
  public:

    /** Creates a shared pointer to a new `trivial_render_manager` instance. */
    static render_manager::ptr create();

    ~trivial_render_manager();

    /* -- `render_manager` Interface Implementation -- */

    virtual void run(const ogl::render_run_args& args);

  private:

    trivial_render_manager();

  };

}

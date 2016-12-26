/**
 * @file	render_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include "app/render_manager.hpp"
#include "app/resource_manager.hpp"

/* -- Types -- */

namespace ogl
{
  namespace simple
  {

    /**
     * Struct containing objects needed to construct an `ogl::simple::render_manager` object.
     */
    struct render_manager_args
    {
      ogl::resource_manager::const_ptr resource_manager;
    };

    /**
     * Class for performing simple rendering.
     */
    class render_manager : public ogl::render_manager
    {
    public:

      /** Creates a shared pointer to a new `render_manager` instance. */
      static ogl::render_manager::ptr create(const ogl::simple::render_manager_args& args);

      ~render_manager();

      /* -- `render_manager` Interface Implementation -- */

      virtual void run(const ogl::render_run_args& args);

    private:

      const ogl::resource_manager::const_ptr m_resource_manager;

      render_manager(const ogl::simple::render_manager_args& args);

    };

  }
}

/**
 * @file	state_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>

#include "app/input_manager.hpp"
#include "app/resource_manager.hpp"
#include "app/state_manager.hpp"

/* -- Types -- */

namespace ogl
{
  namespace simple
  {

    /**
     * Struct containing objects needed to construct an `ogl::simple::state_manager` object.
     */
    struct state_manager_args
    {
      ogl::resource_manager::const_ptr resource_manager;
      ogl::input_manager::const_ptr input_manager;
    };

    /**
     * Basic simple state manager object.
     */
    class state_manager
      : public ogl::state_manager,
	public ogl::input_observer
    {
    public:

      /** Creates a shared pointer to a new `state_manager` instance. */
      static ogl::state_manager::ptr create(const ogl::simple::state_manager_args& args);

      ~state_manager();

      /** The background color to render. */
      glm::vec3 background_color() const
      { return m_background_color; }

      /* -- `state_manager` Interface Implementation -- */

      virtual void run(const ogl::state_run_args& args);

      /* -- `input_observer` Interface Implementation -- */

      virtual void command_activated(ogl::input_command command);
      virtual void command_deactivated(ogl::input_command command);

    private:

      const ogl::input_manager::const_ptr m_input_manager;
      const ogl::resource_manager::const_ptr m_resource_manager;
      glm::vec3 m_background_color;

      state_manager(const ogl::simple::state_manager_args& args);

      void update_background_color(const ogl::state_run_args& args);

    };

  }
}

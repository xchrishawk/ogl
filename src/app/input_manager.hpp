/**
 * @file	input_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

#pragma once

/* -- Includes -- */

#include <memory>

#include "window/window.hpp"
#include "window/window_key.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class responsible for collecting and distributing inputs to the application.
   */
  class input_manager : public window_key_observer
  {
  public:

    /** Shared pointer to an `input_manager` object. */
    typedef std::shared_ptr<input_manager> ptr;

    /** Shared pointer to a `const input_manager` object. */
    typedef std::shared_ptr<const input_manager> const_ptr;

    /** Creates a new `input_manager` instance. */
    static input_manager::ptr create();

    /* -- `window_key_observer` Interface Implementation -- */

    virtual void window_key_pressed(const ogl::window* window,
				    ogl::window_key key,
				    ogl::window_key_action action);

  private:

    input_manager();
    input_manager(const input_manager&) = delete;
    input_manager operator =(const input_manager&) = delete;

  };

}

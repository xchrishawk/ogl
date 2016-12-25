/**
 * @file	input_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <vector>

#include "window/window.hpp"
#include "window/window_key.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Enumeration of input keys which may be pressed by the user.
   */
  enum class input_key : int
  {
    invalid,
    application_exit,
  };

  /**
   * Abstract interface for classes observing inputs from the `input_manager` class.
   */
  class input_observer
  {
  public:

    /** Notifies the observer that an input key was activated. */
    virtual void input_key_activated(ogl::input_key key) { }

    /** Notifies the observer that an input key was deactivated. */
    virtual void input_key_deactivated(ogl::input_key key) { }

  };

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

    /** Adds an `input_observer` to the observer list. */
    void add_observer(input_observer* observer) const;

    /** Removes an `input_observer` from the observer list. */
    void remove_observer(input_observer* observer) const;

    /* -- `window_key_observer` Interface Implementation -- */

    virtual void window_key_pressed(const ogl::window* window,
				    ogl::window_key key,
				    ogl::window_key_action action);

  private:

    mutable std::vector<input_observer*> m_observers;

    input_manager();
    input_manager(const input_manager&) = delete;
    input_manager operator =(const input_manager&) = delete;

    void notify_input_key_activated(ogl::input_key key) const;
    void notify_input_key_deactivated(ogl::input_key key) const;

  };

}

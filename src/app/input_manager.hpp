/**
 * @file	input_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/24
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <vector>

#include "util/debug.hpp"
#include "util/misc.hpp"
#include "window/window.hpp"
#include "window/window_key.hpp"

/* -- Constants -- */

namespace ogl
{

  /**
   * Enumeration of input commands which may be selected by the user.
   */
  enum class input_command : int
  {
    invalid,
    application_exit,
    count,
  };

}

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for classes observing inputs from the `input_manager` class.
   */
  class input_observer
  {
  public:

    /** Notifies the observer that an input command was activated. */
    virtual void command_activated(ogl::input_command command) { }

    /** Notifies the observer that an input command was deactivated. */
    virtual void command_deactivated(ogl::input_command command) { }

  };

  /**
   * Struct containing key mappings for a particular key.
   */
  union input_command_map
  {

    /** Mapping expressed as an array. */
    ogl::input_command map[ogl::enum_count<window_key_modifier>()];

    /** Mapping expressed as a struct. */
    struct
    {
      ogl::input_command invalid;	/**< Not used. */
      ogl::input_command none;		/**< Command when no modifier is pressed. */
      ogl::input_command shift;		/**< Command when shift modifier is pressed. */
      ogl::input_command control;	/**< Command when control modifier is pressed. */
      ogl::input_command alt;		/**< Command when alt modifier is pressed. */
      ogl::input_command super;		/**< Command when super modifier is pressed. */
    } mods;

    /** Returns the input command for the specified modifier. */
    ogl::input_command command_map(ogl::window_key_modifier mod) const;

    /** Sets the input command for the specified modifier. */
    void set_command_map(ogl::window_key_modifier mod, ogl::input_command command);

  };

  // sanity check
  ogl_static_assert(
    sizeof(ogl::input_command_map) == sizeof(ogl::input_command) * ogl::enum_count<ogl::window_key_modifier>(),
    "Invalid struct size!");

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
    void add_observer(ogl::input_observer* observer) const;

    /** Removes an `input_observer` from the observer list. */
    void remove_observer(ogl::input_observer* observer) const;

    /** Returns `true` if the specified command is active. */
    bool command_active(ogl::input_command command) const;

    /** Sets the default command map. */
    void default_command_map();

    /** Gets the `input_command` associated with the specified key press. */
    ogl::input_command command_map(ogl::window_key key, ogl::window_key_modifier mod) const;

    /** Sets the `input_command` associated with the specified key press. */
    void set_command_map(ogl::window_key key, ogl::window_key_modifier mod, ogl::input_command command);

    /* -- `window_key_observer` Interface Implementation -- */

    virtual void window_key_pressed(const ogl::window* window,
				    ogl::window_key key,
				    ogl::window_key_modifier mod,
				    ogl::window_key_action action);

  private:

    std::vector<ogl::input_command_map> m_command_map;
    std::vector<bool> m_command_active;
    mutable std::vector<ogl::input_observer*> m_observers;

    input_manager();
    input_manager(const input_manager&) = delete;
    input_manager operator =(const input_manager&) = delete;

    void notify_command_activated(ogl::input_command key) const;
    void notify_command_deactivated(ogl::input_command key) const;

  };

}

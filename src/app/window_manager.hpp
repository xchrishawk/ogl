/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for types representing a window manager library.
   */
  class window_manager
  {
  public:

    typedef std::shared_ptr<window_manager> ptr;
    typedef std::shared_ptr<const window_manager> const_ptr;

    virtual ~window_manager() { }

  protected:

    window_manager() { }

  private:

    window_manager(const ogl::window_manager&) = delete;
    ogl::window_manager& operator =(const ogl::window_manager&) = delete;

  };

}

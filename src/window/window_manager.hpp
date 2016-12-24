/**
 * @file	window_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for classes representing a window manager.
   */
  class window_manager
  {
  public:

    /** Shared pointer to a `window_manager` object. */
    typedef std::shared_ptr<window_manager> ptr;

    /** Shared pointer to a `const window_manager` object. */
    typedef std::shared_ptr<const window_manager> const_ptr;

    virtual ~window_manager() { }

  protected:

    window_manager() { }

  private:

    window_manager(const window_manager&) = delete;
    window_manager& operator =(const window_manager&) = delete;

  };

}

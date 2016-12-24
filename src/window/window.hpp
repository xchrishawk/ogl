/**
 * @file	window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Includes -- */

#include <memory>
#include <string>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for types representing a window.
   */
  class window
  {
  public:

    /** Shared pointer to a `window` object. */
    typedef std::shared_ptr<window> ptr;

    /** Shared pointer to a `const window` object. */
    typedef std::shared_ptr<const window> const_ptr;

    virtual ~window() { }

    /** Returns `true` if the user has requested that the window close. */
    virtual bool should_close() const = 0;

    /** Sets the "should close" flag. */
    virtual void set_should_close(bool should_close) = 0;

    /** Returns the title of the window. */
    virtual std::string title() const = 0;

    /** Sets the title of the window. */
    virtual void set_title(const std::string& title) = 0;

  protected:

    window() { }

  private:

    window(const window&) = delete;
    window& operator =(const window&) = delete;

  };

}

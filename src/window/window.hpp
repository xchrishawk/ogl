/**
 * @file	window.hpp
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

  protected:

    window() { }

  private:

    window(const window&) = delete;
    window& operator =(const window&) = delete;

  };

}

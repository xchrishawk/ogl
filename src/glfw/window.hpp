/**
 * @file	window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * Wrapper for a GLFW window.
   */
  class window
  {
  public:

    typedef std::shared_ptr<window> ptr;
    typedef std::shared_ptr<const window> const_ptr;

    static window::ptr create();

    ~window();

  private:

    window();
    window(const window&) = delete;
    window& operator =(const window&) = delete;

  };

}

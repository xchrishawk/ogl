/**
 * @file	window.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/28
 */

#pragma once

/* -- Types -- */

namespace app
{

  /**
   * Abstract interface for types representing a window.
   */
  class window
  {
  public:

    virtual ~window() = default;

  protected:

    window() = default;

  private:

    window(const app::window&) = delete;
    app::window& operator =(const app::window&) = delete;

  };

}

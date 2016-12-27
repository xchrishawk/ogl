/**
 * @file	cleanup.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

#pragma once

/* -- Includes -- */

#include <functional>

/* -- Types -- */

namespace ogl
{

  /**
   * Class for objects performing a cleanup action when they go out of scope.
   */
  class cleanup
  {
  public:

    /** Creates a new `cleanup` instance wrapping the specified action. */
    cleanup(const std::function<void(void)>& action)
      : m_action(action)
    { }

    ~cleanup()
    {
      m_action();
    }

  private:

    const std::function<void(void)> m_action;

    cleanup(const cleanup&) = delete;
    cleanup& operator =(const cleanup&) = delete;

  };

}

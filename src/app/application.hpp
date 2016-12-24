/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/23
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  /**
   * Main class for the OGL application.
   */
  class application
  {
  public:

    application();
    ~application();

    /** Runs the main loop for the application. */
    void main();

  private:

    static application* s_instance;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}

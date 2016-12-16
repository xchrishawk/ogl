/**
 * application.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  /** Main application singleton class. */
  class application
  {
  public:

    /** The singleton application instance. */
    static application& instance();

    ~application();

    /** Main application procedure. */
    void main();

  private:

    application();
    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}

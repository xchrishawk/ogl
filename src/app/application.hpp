/**
 * application.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include "opengl/opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /** Main application singleton class. */
  class application
  {
  public:

    application(const opengl_factory& opengl_fact);
    ~application();

    /** Main application procedure. */
    void main();

  private:

    static application* m_instance;
    const opengl::ptr m_opengl;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}

/**
 * application.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Includes -- */

#include "opengl/opengl.hpp"
#include "opengl/glfw/glfw.hpp"
#include "opengl/glfw/window.hpp"

/* -- Types -- */

namespace ogl
{

  /** Main application singleton class. */
  class application
  {
  public:

    application(const glfw_factory& glfw_fact,
		const opengl_factory& opengl_fact);
    ~application();

    /** Main application procedure. */
    void main();

  private:

    static application* m_instance;

    const glfw::ptr m_glfw;
    const opengl::ptr m_opengl;

    application(const application&) = delete;
    application& operator =(const application&) = delete;

  };

}

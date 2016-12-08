/**
 * application.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_APPLICATION_HPP
#define OGL_APP_APPLICATION_HPP

/* -- Includes -- */

#include "app/input.hpp"
#include "opengl/glew.hpp"
#include "opengl/glfw.hpp"
#include "opengl/window.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Main class for the OGL application.
   */
  class application
  {
  public:

    static application& instance();

    ~application();

    void main();
    float time() const;

  private:

    ogl::glfw m_glfw;
    ogl::window m_window;
    ogl::glew m_glew;
    ogl::input m_input;

    application();
    application(const application& other) = delete;
    application& operator =(const application& other) = delete;

    void handle_app_input();

    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  };

}

#endif /* OGL_APP_APPLICATION_HPP */

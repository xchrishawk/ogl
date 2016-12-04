/**
 * application.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

/* -- Includes -- */

#include "glew.hpp"
#include "glfw.hpp"
#include "window.hpp"

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
    float time();

  private:

    glfw m_glfw;
    window m_window;
    glew m_glew;

    application();
    application(const application& other) = delete;
    application& operator =(const application& other) = delete;

    void state_main(float abs_t, float delta_t);
    void render_main(float abs_t, float delta_t);

  };

}

#endif /* APPLICATION_HPP */

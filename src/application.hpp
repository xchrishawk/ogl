/**
 * application.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

/* -- Includes -- */

#include "glfw.hpp"

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

  private:

    glfw m_glfw;

    application();
    application(const application& other) = delete;
    application& operator =(const application& other) = delete;

  };

}

#endif /* APPLICATION_HPP */

/**
 * application.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_APPLICATION_HPP
#define OGL_APP_APPLICATION_HPP

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

    application();
    application(const application& other) = delete;
    application& operator =(const application& other) = delete;

  };

}

#endif /* OGL_APP_APPLICATION_HPP */

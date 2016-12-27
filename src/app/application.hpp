/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing objects required to construct an `ogl::application` instance.
   */
  struct application_args
  {

  };

  /**
   * Main application class.
   */
  class application
  {
  public:

    /** Shared pointer to an `ogl::application` instance. */
    typedef std::shared_ptr<application> ptr;

    /** Shared pointer to a `const ogl::application` instance. */
    typedef std::shared_ptr<const application> const_ptr;

    /** Creates a shared pointer to a new `ogl::application` instance. */
    static ogl::application::ptr create(const ogl::application_args& args)
    {
      return ogl::application::ptr(new ogl::application(args));
    }

    ~application();

    /** Runs the main loop for the application. */
    void main();

  private:

    application(const ogl::application_args& args);
    application(const ogl::application&) = delete;
    application& operator =(const ogl::application&) = delete;

  };

}

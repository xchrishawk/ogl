/**
 * @file	application.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/27
 */

#pragma once

/* -- Includes -- */

#include <memory>

#include "app/window_manager.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing objects required to construct an `ogl::application` instance.
   */
  struct application_args
  {
    std::shared_ptr<ogl::window_manager> window_manager;
  };

  /**
   * Main application class.
   */
  class application
  {
  public:

    /**
     * Creates a shared pointer to a new `ogl::application` instance.
     *
     * @param args
     * Struct containing objects required to construct the application.
     *
     * @exception std::invalid_argument
     * Thrown if any required argument value is invalid.
     */
    static auto create(const ogl::application_args& args)
    {
      return std::shared_ptr<ogl::application>(new ogl::application(args));
    }

    ~application();

    /** Runs the main loop for the application. */
    void main();

  private:

    const std::shared_ptr<ogl::window_manager> window_manager_;

    application(const ogl::application_args& args);
    application(const ogl::application&) = delete;
    application& operator =(const ogl::application&) = delete;

  };

}

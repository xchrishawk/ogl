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

namespace app
{

  /**
   * Struct containing objects required to construct an `app::application` instance.
   */
  struct application_args
  {
    std::shared_ptr<app::window_manager> window_manager;
  };

  /**
   * Main application class.
   */
  class application
  {
  public:

    /**
     * Creates a shared pointer to a new `app::application` instance.
     *
     * @param args
     * Struct containing objects required to construct the application.
     *
     * @exception std::invalid_argument
     * Thrown if any required argument value is invalid.
     */
    static auto create(const app::application_args& args)
    {
      return std::shared_ptr<app::application>(new app::application(args));
    }

    ~application();

    /** Runs the main loop for the application. */
    void main();

  private:

    const std::shared_ptr<app::window_manager> window_manager_;

    application(const app::application_args& args);
    application(const app::application&) = delete;
    application& operator =(const app::application&) = delete;

  };

}

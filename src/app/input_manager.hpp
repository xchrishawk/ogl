/**
 * @file	input_manager.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

#pragma once

/* -- Includes -- */

/* -- Types -- */

namespace ogl
{

  /**
   * Class responsible for handling inputs to the application.
   */
  class input_manager
  {
  public:

    /**
     * Handles the specified keypress.
     *
     * @note
     * This should only be called by the `application` class to handle key press
     * events from the GLFW window.
     */
    void handle_keypress(int key, int scancode, int action, int mods);

  private:

  };

}

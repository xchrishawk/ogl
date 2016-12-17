/**
 * @file	opengl.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  /**
   * Class wrapping the platform-specific OpenGL loader library.
   */
  class opengl
  {
  public:

    opengl();
    ~opengl();

  private:

    static opengl* s_instance;

    opengl(const opengl&) = delete;
    opengl& operator =(const opengl&) = delete;

    void print_version_info();

  };

}

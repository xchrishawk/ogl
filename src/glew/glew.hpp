/**
 * @file	glew.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  /**
   * RAII wrapper for the GLEW library.
   */
  class glew
  {
  public:

    glew();
    ~glew();

  private:

    static glew* s_instance;

    glew(const glew&) = delete;
    glew& operator =(const glew&) = delete;

  };

}

/**
 * glew.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

#if !defined(OGL_LINUX)
  #error This file should only be included on Linux!
#endif

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

    glew(const glew&) = delete;
    glew& operator =(const glew&) = delete;

  };

}

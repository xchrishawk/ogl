/**
 * glew.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef GLEW_HPP
#define GLEW_HPP

/* -- Types -- */

namespace ogl
{

  /**
   * Class providing an RAII wrapper for the GLEW library.
   */
  class glew
  {
  public:

    glew(bool experimental);
    ~glew();

  private:

    static bool initialized;

    glew(const glew& other) = delete;
    glew& operator =(const glew& other) = delete;

  };

}

#endif /* GLEW_HPP */

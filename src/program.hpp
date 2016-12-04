/**
 * program.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

/* -- Includes -- */

#include <memory>
#include <vector>

#include "opengl.hpp"
#include "shader.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing an OpenGL program.
   */
  class program
  {
  public:

    typedef std::shared_ptr<program> ptr;

    static ptr create();
    ~program();

    GLuint id() const { return m_id; }

  private:

    GLuint m_id;

    program();
    program(const program& other) = delete;
    program& operator =(const program& other) = delete;

  };

}

#endif /* PROGRAM_HPP */

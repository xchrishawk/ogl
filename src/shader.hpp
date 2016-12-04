/**
 * shader.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef SHADER_HPP
#define SHADER_HPP

/* -- Includes -- */

#include <string>
#include "opengl.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing an OpenGL shader.
   */
  class shader
  {

  public:

    shader(GLenum type);
    ~shader();

    void set_source(const std::string& source);
    void compile();
    bool is_compiled() const;
    std::string info_log() const;

  private:

    const GLenum m_type;
    const GLuint m_id;

    shader(const shader& other) = delete;
    shader& operator =(const shader& other) = delete;

  };

}

#endif /* SHADER_HPP */

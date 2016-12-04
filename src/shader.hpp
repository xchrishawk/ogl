/**
 * shader.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef SHADER_HPP
#define SHADER_HPP

/* -- Includes -- */

#include <memory>
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

    typedef std::shared_ptr<shader> ptr;

    static ptr create(GLenum type);
    ~shader();

    void set_source(const std::string& source);
    void load_source(const std::string& filename);
    void compile();

    GLenum type() const { return m_type; }
    GLuint id() const { return m_id; }
    bool is_compiled() const;
    std::string info_log() const;

  private:

    const GLenum m_type;
    const GLuint m_id;

    shader(GLenum type);
    shader(const shader& other) = delete;
    shader& operator =(const shader& other) = delete;

  };

}

#endif /* SHADER_HPP */

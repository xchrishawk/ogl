/**
 * shader.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_SHADER_HPP
#define OGL_OPENGL_SHADER_HPP

/* -- Includes -- */

#include <memory>
#include <string>

#include "opengl/opengl.hpp"

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
    typedef std::shared_ptr<const shader> const_ptr;

    static ptr create(GLenum type);
    ~shader();

    void set_source(const std::string& source);
    void load_source(const std::string& filename);
    void compile();

    GLenum type() const { return m_type; }
    GLuint handle() const { return m_handle; }
    bool is_compiled() const;
    std::string info_log() const;

  private:

    const GLenum m_type;
    const GLuint m_handle;

    shader(GLenum type);
    shader(const shader& other) = delete;
    shader& operator =(const shader& other) = delete;

    static GLuint new_handle(GLenum type);

  };

}

#endif /* OGL_OPENGL_SHADER_HPP */

/**
 * program.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

/* -- Includes -- */

#include <memory>
#include <string>
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
    typedef std::shared_ptr<const program> const_ptr;

    static ptr create();
    static void unactivate();

    ~program();

    void attach_shader(shader::const_ptr shader);
    void attach_shaders(const std::vector<shader::const_ptr>& shaders);
    void detach_shader(shader::const_ptr shader);
    void detach_shaders(const std::vector<shader::const_ptr>& shaders);

    void link();
    void activate() const;

    GLuint id() const { return m_id; }
    bool is_linked() const;
    std::string info_log() const;

    GLint attribute_location(const std::string& name);
    GLint uniform_location(const std::string& name);

  private:

    GLuint m_id;

    program();
    program(const program& other) = delete;
    program& operator =(const program& other) = delete;

  };

}

#endif /* PROGRAM_HPP */

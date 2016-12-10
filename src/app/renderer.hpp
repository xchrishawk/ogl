/**
 * renderer.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_RENDERER_HPP
#define OGL_APP_RENDERER_HPP

/* -- Includes -- */

#include "opengl/buffer.hpp"
#include "opengl/program.hpp"
#include "opengl/vertex_array.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Primary class reponsible for OpenGL rendering.
   */
  class renderer
  {
  public:

    renderer();
    ~renderer();

    void render(float abs_t, float delta_t);

  private:

    ogl::vertex_array::ptr m_vao;
    ogl::program::ptr m_program;

    ogl::immutable_buffer::ptr m_buffer_1;
    ogl::immutable_buffer::ptr m_buffer_2;

    renderer(const renderer&) = delete;
    renderer& operator =(const renderer&) = delete;

    ogl::program::ptr init_program();
    void init_attribute_binding(const std::string& attribute_name,
				GLuint binding_index,
				GLint size,
				GLint relative_offset);
    void clear_buffer();

  };

}

#endif /* OGL_APP_RENDERER_HPP */

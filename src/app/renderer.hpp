/**
 * renderer.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_RENDERER_HPP
#define OGL_APP_RENDERER_HPP

/* -- Includes -- */

#include <vector>

#include "app/mesh.hpp"
#include "app/state.hpp"
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

    void render(int width, int height, const ogl::state& state);

  private:

    ogl::vertex_array::ptr m_vao;
    ogl::program::ptr m_program;

    renderer(const renderer&) = delete;
    renderer& operator =(const renderer&) = delete;

    ogl::program::ptr init_program();
    void clear_buffer(int width, int height);

  };

}

#endif /* OGL_APP_RENDERER_HPP */

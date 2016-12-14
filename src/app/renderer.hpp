/**
 * renderer.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_RENDERER_HPP
#define OGL_APP_RENDERER_HPP

/* -- Includes -- */

#include <vector>

#include "app/state.hpp"
#include "opengl/program.hpp"
#include "opengl/vertex_array.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class containing information needed for a rendering cycle.
   */
  class renderer_args
  {
  public:

    renderer_args(int width, int height, const ogl::state& state)
      : width(width),
	height(height),
	state(state)
    { }

    const int width;
    const int height;
    const ogl::state& state;

  };

  /**
   * Primary class reponsible for OpenGL rendering.
   */
  class renderer
  {
  public:

    renderer();
    ~renderer();

    void render(const ogl::renderer_args& args);

  private:

    ogl::vertex_array::ptr m_vao;
    ogl::program::ptr m_program;

    renderer(const renderer&) = delete;
    renderer& operator =(const renderer&) = delete;

    ogl::program::ptr init_program();
    ogl::vertex_array::ptr init_vertex_array(ogl::program::ptr program);

    void clear_buffer(int width, int height);
    void render_object(const ogl::object& obj, const glm::mat4& vp);
    void render_mesh_elements(const ogl::mesh_elements& elements);

    glm::mat4 view_proj_matrix(int width, int height, const ogl::state& state);
    glm::mat4 model_matrix(const ogl::object& obj);

  };

}

#endif /* OGL_APP_RENDERER_HPP */

/**
 * @file	renderer.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

#pragma once

/* -- Includes -- */

#include <glm/glm.hpp>

#include "opengl/program.hpp"
#include "opengl/vertex_array.hpp"
#include "scene/scene.hpp"
#include "scene/object.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct containing information required to run a render loop.
   */
  class render_args
  {
  public:

    render_args(const ogl::scene& scene,
		double abs_t,
		double delta_t,
		int framebuffer_width,
		int framebuffer_height)
      : scene(scene),
	abs_t(abs_t),
	delta_t(delta_t),
	framebuffer_width(framebuffer_width),
	framebuffer_height(framebuffer_height)
    { }

    const ogl::scene& scene;
    const double abs_t;
    const double delta_t;
    const int framebuffer_width;
    const int framebuffer_height;

  };

  /**
   * Class responsible for rendering the app's graphics.
   */
  class renderer
  {
  public:

    renderer();
    ~renderer();

    /** Renders a frame to the current OpenGL context. */
    void render(const render_args& args);

  private:

    static program::ptr init_program();
    static vertex_array::ptr init_vao(const program::const_ptr& program);

    const program::ptr m_program;
    const vertex_array::ptr m_vao;

    renderer(const renderer&) = delete;
    renderer& operator =(const renderer&) = delete;

    void enable_depth_testing();
    void enable_face_culling();

    void clear_buffer(const render_args& args);
    void draw_scene(const render_args& args);
    void draw_object(const object& object);
    void draw_mesh(const mesh& mesh);

    glm::mat4 model_matrix(const object& object, const component& component);
    glm::mat4 view_matrix(const render_args& args);
    glm::mat4 projection_matrix(const render_args& args);

    void set_vec3_uniform(const std::string& name, const glm::vec3& vector);
    void set_vec4_uniform(const std::string& name, const glm::vec4& vector);
    void set_matrix_uniform(const std::string& name, const glm::mat4& matrix);

  };

}

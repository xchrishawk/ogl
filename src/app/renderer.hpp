/**
 * renderer.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_APP_RENDERER_HPP
#define OGL_APP_RENDERER_HPP

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

    renderer(const renderer&) = delete;
    renderer& operator =(const renderer&) = delete;

    void clear_buffer();

  };

}

#endif /* OGL_APP_RENDERER_HPP */

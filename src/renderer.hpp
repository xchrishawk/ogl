/**
 * renderer.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP

/* -- Includes -- */

#include "state.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class responsible for performing OpenGL rendering.
   */
  class renderer
  {
  public:

    renderer();

    void loop(const state& state);

  private:

    renderer(const renderer& other) = delete;
    renderer& operator =(const renderer& other) = delete;

    void clear();

  };

}

#endif /* RENDERER_HPP */

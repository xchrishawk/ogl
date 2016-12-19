/**
 * @file	opengl.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Types -- */

namespace ogl
{

  /**
   * Class wrapping the platform-specific OpenGL loader library.
   */
  class opengl
  {
  public:

    opengl();
    ~opengl();

    /** Returns the `GL_VERSION` string for the OpenGL implementation. */
    std::string version() const;

    /** Returns the `GL_SHADING_LANGUAGE_VERSION` string for the OpenGL implementation. */
    std::string glsl_version() const;

    /** Returns the `GL_VENDOR` string for the OpenGL implementation. */
    std::string vendor() const;

    /** Returns the `GL_RENDERER` string for the OpenGL implementation. */
    std::string renderer() const;

  private:

    static opengl* s_instance;

    opengl(const opengl&) = delete;
    opengl& operator =(const opengl&) = delete;

    void check_required_extensions() const;

  };

}

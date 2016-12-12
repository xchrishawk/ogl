/**
 * texture.hpp
 * Chris Vig (chris@invictus.so)
 */

#ifndef OGL_OPENGL_TEXTURE_HPP
#define OGL_OPENGL_TEXTURE_HPP

/* -- Includes -- */

#include <memory>
#include <GL/glew.h>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract base class representing an OpenGL texture object.
   */
  class texture
  {
  public:

    virtual ~texture();

    GLenum target() const { return m_target; }
    GLuint handle() const { return m_handle; }

    void set_wrap_x(GLint wrap);
    void set_wrap_y(GLint wrap);
    void set_wrap_z(GLint wrap);
    void set_border_color(float r, float g, float b, float a);
    void set_min_filter(GLint filter);
    void set_mag_filter(GLint filter);

  protected:

    texture(GLenum target);

  private:

    const GLenum m_target;
    const GLuint m_handle;

    texture(const texture&) = delete;
    texture& operator =(const texture&) = delete;

    static GLuint new_handle(GLenum target);

  };

  /**
   * Class representing a 2-dimensional texture.
   */
  class texture2d : public texture
  {
  public:

    typedef std::shared_ptr<texture2d> ptr;
    typedef std::shared_ptr<const texture2d> const_ptr;

    static ptr create(GLsizei levels,
		      GLenum internal_format,
		      GLsizei width,
		      GLsizei height);

    void set_image(GLint level,
		   GLint x_offset,
		   GLint y_offset,
		   GLsizei width,
		   GLsizei height,
		   GLenum format,
		   GLenum type,
		   const void* pixels);

  private:

    const GLsizei m_levels;
    const GLenum m_internal_format;
    const GLsizei m_width;
    const GLsizei m_height;

    texture2d(GLsizei levels,
	      GLenum internal_format,
	      GLsizei width,
	      GLsizei height);

  };

}

#endif /* OGL_OPENGL_TEXTURE_HPP */

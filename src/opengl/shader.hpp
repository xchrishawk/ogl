/**
 * @file	shader.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

/* -- Includes -- */

#include <memory>
#include <string>

#include "opengl/api.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing an OpenGL shader.
   */
  class shader
  {
  public:

    /** Shared pointer to an `ogl::shader` object. */
    typedef std::shared_ptr<shader> ptr;

    /**
     * Creates a new shader of the specified type.
     *
     * @param type
     * The type of shader to create.
     *
     * @exception ogl::alloc_exception
     * Thrown if a new shader object cannot be created.
     */
    static ptr create(GLenum type);

    ~shader();

    /** Sets the source code for the shader. */
    void set_source(const std::string& source);

    /**
     * Loads the source code of the shader from a file.
     *
     * @param filename
     * The name of the file to load.
     *
     * @exception ogl::file_io_exception
     * Thrown if the file cannot be loaded.
     */
    void load_source(const std::string& filename);

    /**
     * Compiles the shader with the currently set source code.
     *
     * @exception ogl::shader_exception
     * Thrown if the compilation fails for any reason.
     */
    void compile();

    /** Returns the OpenGL shader type. */
    GLenum type() const { return m_type; }

    /** Returns the internal OpenGL handle for this shader. */
    GLuint handle() const { return m_handle; }

    /** Returns `true` if the shader has been successfully compiled. */
    bool is_compiled() const;

    /** Returns the OpenGL info log string for this shader. */
    std::string info_log() const;

  private:

    const GLenum m_type;
    const GLuint m_handle;

    shader(GLenum type);
    shader(const shader& other) = delete;
    shader& operator =(const shader& other) = delete;

    static GLuint new_handle(GLenum type);
    static std::string shader_type_name(GLenum type);

  };

}

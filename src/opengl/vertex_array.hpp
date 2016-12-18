/**
 * @file	vertex_array.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/17
 */

#pragma once

/* -- Includes -- */

#include <memory>

#include "opengl/api.hpp"
#include "opengl/buffer.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class representing an OpenGL vertex array object (VAO).
   */
  class vertex_array
  {
  public:

    /** Shared pointer to an `ogl::vertex_array` object. */
    typedef std::shared_ptr<vertex_array> ptr;

    /** SHared pointer to a constant `ogl::vertex_array` object. */
    typedef std::shared_ptr<const vertex_array> const_ptr;

    /**
     * Creates a new vertex array object.
     *
     * @exception ogl::alloc_exception
     * Thrown if a new vertex array cannot be created.
     */
    static ptr create();

    /** Sets the specified vertex array as the active vertex array. */
    static void bind(const vertex_array::const_ptr& vao);

    /** Deactivates the currently active vertex array, if there is one. */
    static void bind_none();

    ~vertex_array();

    /**
     * Sets the format to use for a vertex buffer binding.
     *
     * This calls `glVertexArrayAttribFormat()`, `glVertexArrayAttribBinding()`,
     * and `glEnableVertexArrayAttrib()` to completely set up a binding for a
     * vertex buffer object (VBO). Currently the type is hard-coded to GL_FLOAT,
     * and the normalized setting is hard-coded to GL_FALSE.
     *
     * Note that this function only sets the format of the VBO. A buffer must
     * actually be bound by calling `activate_vertex_buffer` before values will
     * actually be fed into the pipeline.
     *
     * @param binding_index
     * The index of the binding to which this format should be added.
     *
     * @param attribute_index
     * The location of the attribute to be bound using this format.
     *
     * @param size
     * The number of values per vertex that are stored in the buffer for this
     * attribute.
     *
     * @param relative_offset
     * The offset into each vertex record of the values for this attribute.
     */
    void vertex_buffer_format(GLuint binding_index,
			      GLuint attribute_index,
			      GLint size,
			      GLint relative_offset);

    /**
     * Binds a buffer for use with a previously configured vertex binding.
     *
     * This associates a specific OpenGL buffer with a binding index set up by
     * previous call(s) to `vertex_buffer_format`. It calls `glVertexArrayVertexBuffer()`
     * to activate the binding.
     *
     * @param binding_index
     * The binding index to associate this buffer with.
     *
     * @param buffer
     * The buffer to use for the binding index.
     *
     * @param stride
     * The total size of each vertex record in the buffer.
     *
     * @param offset
     * The offset of the initial vertex record in the buffer.
     */
    void bind_vertex_buffer(GLuint binding_index,
			    const buffer::const_ptr& buffer,
			    GLsizei stride,
			    GLintptr offset);

    /** Unbinds any buffer associated with the specified binding index. */
    void unbind_vertex_buffer(GLuint binding_index);

    /** Returns the internal OpenGL handle for this vertex array. */
    GLuint handle() const { return m_handle; }

  private:

    GLuint m_handle;

    vertex_array();
    vertex_array(const vertex_array& other) = delete;
    vertex_array& operator =(const vertex_array& other) = delete;

    static GLuint new_handle();

  };

}

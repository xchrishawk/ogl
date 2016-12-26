/**
 * @file	opengl_program.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/25
 */

#pragma once

/* -- Includes -- */

#include <string>
#include <vector>

#include <GL/glew.h>

#include "opengl/program.hpp"
#include "opengl/shader.hpp"

/* -- Types -- */

namespace ogl
{
  namespace impl
  {

    /**
     * Concrete implementation of the `ogl::program` interface.
     */
    class opengl_program final : public program
    {
    public:

      /**
       * Creates a shared pointer to a new `opengl_program` instance.
       *
       * @exception ogl::opengl_exception
       * Thrown if the program cannot be created for any reason.
       */
      static ogl::program::ptr create();

      ~opengl_program();

      /* -- `program` Interface Implementation -- */

      virtual void link(const std::vector<ogl::shader::const_ptr>& shaders);
      virtual bool is_linked() const;
      virtual int attribute_count() const;
      virtual int attribute_index(const std::string& name) const;
      virtual int uniform_count() const;
      virtual int uniform_index(const std::string& name) const;
      virtual std::string info_log() const;

    private:

      const GLuint m_handle;

      opengl_program();

    };

  }
}

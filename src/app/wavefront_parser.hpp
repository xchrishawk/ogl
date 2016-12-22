/**
 * @file	wavefront_parser.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

#pragma once

/* -- Includes -- */

#include <regex>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "opengl/api.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Class for parsing Wavefront OBJ model files.
   */
  class wavefront_parser
  {
  public:

    /**
     * Parses the OBJ file at the specified filename.
     *
     * @exception ogl::file_io_exception
     * Thrown if the file cannot be opened, or is in an invalid format.
     */
    void parse_file(const std::string& filename,
		    std::vector<glm::vec4>& vertices,
		    std::vector<GLuint>& indices);

  private:

    static const std::regex comment_regex;
    static const std::regex only_whitespace_regex;
    static const std::regex v_regex;
    static const std::regex vt_regex;
    static const std::regex vn_regex;
    static const std::regex f_regex;

    static std::regex vertex_regex(const std::string& type, int mandatory_floats, int optional_floats);

  };

}

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
#include "scene/vertex.hpp"

/* -- Types -- */

namespace ogl
{

  /**
   * Struct representing a vertex in a Wavefront object file.
   */
  struct wavefront_vertex
  {
    float x;
    float y;
    float z;
    float w;

    glm::vec4 to_vec4() const { return glm::vec4(x, y, z, w); }

  };

  /**
   * Struct representing a face in a Wavefront object file.
   */
  struct wavefront_face
  {
    int v1;
    int v2;
    int v3;
  };

  /**
   * Class for parsing Wavefront OBJ model files.
   */
  class wavefront_parser
  {
  public:

    /**
     * Parses a `std::vector` of `ogl::vertex` from the OBJ file at the specifeid filename.
     *
     * @exception ogl::file_io_exception
     * Thrown if the file cannot be opened, or is in an invalid format.
     */
    void parse_file(const std::string& filename,
		    std::vector<vertex>& vertices,
		    std::vector<GLuint>& indices);

  private:

    /**
     * Parses the OBJ file at the specified filename.
     *
     * @exception ogl::file_io_exception
     * Thrown if the file cannot be opened, or is in an invalid format.
     */
    void internal_parse_file(const std::string& filename,
			     std::vector<wavefront_vertex>& vertices,
			     std::vector<wavefront_face>& faces);

    static const std::regex comment_regex;
    static const std::regex only_whitespace_regex;
    static const std::regex v_regex;
    static const std::regex vt_regex;
    static const std::regex vn_regex;
    static const std::regex f_regex;

    static std::regex vertex_regex(const std::string& type, int mandatory_floats, int optional_floats);

  };

}

/**
 * @file	wavefront_file.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

#pragma once

/* -- Includes -- */

#include <regex>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "scene/mesh.hpp"

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
  class wavefront_file
  {
  public:

    /**
     * Creates a new instance with the specified filename.
     *
     * @exception ogl::file_io_exception
     * Thrown if the file cannot be opened, or if it is in an invalid format.
     */
    wavefront_file(const std::string& filename);

    /** Converts this Wavefront file to a mesh. */
    mesh to_mesh() const;

    /** Returns the vertices contained in this Wavefront file. */
    std::vector<wavefront_vertex> vertices() const
    { return m_vertices; }

    /** Returns the faces contained in this Wavefront file. */
    std::vector<wavefront_face> faces() const
    { return m_faces; }

  private:

    static const std::regex comment_regex;
    static const std::regex only_whitespace_regex;
    static const std::regex v_regex;
    static const std::regex vt_regex;
    static const std::regex vn_regex;
    static const std::regex f_regex;
    static const std::regex g_regex;
    static const std::regex s_regex;
    static const std::regex mtllib_regex;
    static const std::regex usemtl_regex;

    static void parse_file(const std::string& filename,
			   std::vector<wavefront_vertex>& vertices,
			   std::vector<wavefront_face>& faces);
    static std::regex vertex_regex(const std::string& type,
				   int mandatory_floats,
				   int optional_floats);

    std::vector<wavefront_vertex> m_vertices;
    std::vector<wavefront_face> m_faces;

  };

}

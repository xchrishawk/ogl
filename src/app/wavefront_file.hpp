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
   * Class representing a vertex (`v` line) in a Wavefront OBJ file.
   */
  class wavefront_vertex
  {
  public:

    /** The prefix for vertex lines. */
    static const std::string prefix;

    /** Creates a new instance from the specified line. */
    wavefront_vertex(const std::string& line);

    float x;	/**< The X position of the vertex. */
    float y;	/**< The Y position of the vertex. */
    float z;	/**< The Z position of the vertex. */
    float w;	/**< The W position of the vertex. */

    /** Returns this vertex as a `glm::vec4`. */
    glm::vec4 to_vec4() const { return glm::vec4(x, y, z, w); }

  private:
    static const std::regex regex;
  };

  /**
   * Class representing a vertex normal (`vn` line) in a Wavefront OBJ file.
   */
  class wavefront_normal
  {
  public:

    /** The prefix for vertex normal lines. */
    static const std::string prefix;

    /** Creates a new instance from the specified line. */
    wavefront_normal(const std::string& line);

    float x;	/**< The X component of the normal. */
    float y;	/**< The Y component of the normal. */
    float z;	/**< The Z component of the normal. */

  private:
    static const std::regex regex;
  };

  /**
   * Class representing a face in a Wavefront OBJ file.
   */
  class wavefront_face
  {
  public:

    /** The prefix for face lines. */
    static const std::string prefix;

    /** Creates a new instance from the specified line. */
    wavefront_face(const std::string& line);

    /** The indices contained in the face. */
    std::vector<int> indices;

  private:
    static const std::regex regex;
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

    /** Converts this file to a mesh. */
    mesh to_mesh() const;

  private:

    std::vector<wavefront_vertex> m_vertices;
    std::vector<wavefront_normal> m_normals;
    std::vector<wavefront_face> m_faces;

    bool begins_with(const std::string& line, const std::string& prefix);

  };

}

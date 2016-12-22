/**
 * @file	wavefront_file.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include <fstream>
#include <regex>
#include <sstream>
#include <string>

#include "app/wavefront_file.hpp"
#include "opengl/api.hpp"
#include "scene/mesh.hpp"
#include "scene/vertex.hpp"
#include "util/debug.hpp"
#include "util/exceptions.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

const std::regex wavefront_file::comment_regex("#.*$");
const std::regex wavefront_file::only_whitespace_regex("^\\s*$");
const std::regex wavefront_file::v_regex = wavefront_file::vertex_regex("v", 3, 1);
const std::regex wavefront_file::vt_regex = wavefront_file::vertex_regex("vt", 2, 1);
const std::regex wavefront_file::vn_regex = wavefront_file::vertex_regex("vn", 3, 0);
const std::regex wavefront_file::f_regex("^\\s*f\\s*([0-9]+)\\s*([0-9]+)\\s*([0-9]+)\\s*$");
const std::regex wavefront_file::g_regex("^\\s*g\\s*(.*)$");
const std::regex wavefront_file::s_regex("^\\s*s\\s*(.*)$");
const std::regex wavefront_file::mtllib_regex("^\\s*mtllib\\s+(.+)$");
const std::regex wavefront_file::usemtl_regex("^\\s*usemtl\\s+(.+)$");

/* -- Procedures -- */

wavefront_file::wavefront_file(const std::string& filename)
{
  wavefront_file::parse_file(filename, m_vertices, m_faces);
}

mesh wavefront_file::to_mesh() const
{
  // build vectors we'll use
  std::vector<vertex> mesh_vertices;
  mesh_vertices.reserve(m_vertices.size());
  std::vector<GLuint> mesh_indices;
  mesh_indices.reserve(m_faces.size() * 3);

  // initialize vertex vector
  for (const auto& vertex : m_vertices)
    mesh_vertices.push_back({ vertex.to_vec4(), glm::vec3() });

  // loop through each face
  for (const auto& face : m_faces)
  {
    // WF indices are 1-based
    auto v1_idx = face.v1 - 1;
    auto v2_idx = face.v2 - 1;
    auto v3_idx = face.v3 - 1;

    // get references to vertices
    vertex& v1 = mesh_vertices[v1_idx];
    vertex& v2 = mesh_vertices[v2_idx];
    vertex& v3 = mesh_vertices[v3_idx];

    // add normal to each vertex
    glm::vec3 normal = cross(glm::vec3(v2.position - v1.position),
			     glm::vec3(v3.position - v1.position));
    v1.normal += normal;
    v2.normal += normal;
    v3.normal += normal;

    // add indices
    mesh_indices.push_back(v1_idx);
    mesh_indices.push_back(v2_idx);
    mesh_indices.push_back(v3_idx);
  }

  // finally, normalize all normals
  for (auto& vertex : mesh_vertices)
    vertex.normal = normalize(vertex.normal);

  // and return the mesh
  return mesh(GL_TRIANGLES, mesh_vertices, mesh_indices);
}

void wavefront_file::parse_file(const std::string& filename,
				std::vector<wavefront_vertex>& vertices,
				std::vector<wavefront_face>& faces)
{
    std::fstream infile(filename);
    if (!infile.is_open())
      throw file_io_exception("Unable to open " + filename);

    int line_number = 0;
    std::string line;
    while (std::getline(infile, line))
    {
      line_number++;

      // drop \r from last character, if the file uses windows line endings
      if (line[line.size() - 1] == '\r')
	line.pop_back();

      // remove comments
      line = std::regex_replace(line, wavefront_file::comment_regex, "");

      // is the line nothing but whitespace?
      if (std::regex_match(line, wavefront_file::only_whitespace_regex))
	continue;

      // check for vertices
      std::smatch results;
      if (std::regex_match(line, results, wavefront_file::v_regex))
      {
	static const auto X_INDEX = 1;
	static const auto Y_INDEX = 6;
	static const auto Z_INDEX = 11;
	static const auto W_INDEX = 16;

	auto x = std::stof(results[X_INDEX]);
	auto y = std::stof(results[Y_INDEX]);
	auto z = std::stof(results[Z_INDEX]);
	auto w = 1.0f;
	if (!results[W_INDEX].str().empty())
	  w = std::stof(results[W_INDEX]);

	vertices.push_back({ x, y, z, w });
	continue;
      }
      else if (std::regex_match(line, results, wavefront_file::vt_regex))
      {
	// static const auto X_INDEX = 1;
	// static const auto Y_INDEX = 6;
	// static const auto Z_INDEX = 11;

	// auto x = std::stof(results[X_INDEX]);
	// auto y = std::stof(results[Y_INDEX]);
	// auto z = 1.0f;
	// if (!results[Z_INDEX].str().empty())
	//   z = std::stof(results[Z_INDEX]);

	//std::cout << "Found texture: " << x << " " << y << " " << z << std::endl;
	continue;
      }
      else if (std::regex_match(line, results, wavefront_file::vn_regex))
      {
	// static const auto X_INDEX = 1;
	// static const auto Y_INDEX = 6;
	// static const auto Z_INDEX = 11;

	// auto x = std::stof(results[X_INDEX]);
	// auto y = std::stof(results[Y_INDEX]);
	// auto z = std::stof(results[Z_INDEX]);

	//std::cout << "Found vertex normal: " << x << " " << y << " " << z << std::endl;
	continue;
      }
      else if (std::regex_match(line, results, wavefront_file::f_regex))
      {
	static const auto V1_INDEX = 1;
	static const auto V2_INDEX = 2;
	static const auto V3_INDEX = 3;

	auto v1 = std::stoi(results[V1_INDEX]);
	auto v2 = std::stoi(results[V2_INDEX]);
	auto v3 = std::stoi(results[V3_INDEX]);

	faces.push_back({ v1, v2, v3 });
	continue;
      }
      else if (std::regex_match(line, results, wavefront_file::g_regex))
      {
	continue;
      }
      else if (std::regex_match(line, results, wavefront_file::s_regex))
      {
	continue;
      }
      else if (std::regex_match(line, results, wavefront_file::mtllib_regex))
      {
	continue;
      }
      else if (std::regex_match(line, results, wavefront_file::usemtl_regex))
      {
	continue;
      }

      // if we get to this point, the line is invalid
      std::ostringstream error_msg;
      error_msg << "Invalid line (line " << line_number << "): " << line;
      throw file_io_exception(error_msg.str());
    }
}


std::regex wavefront_file::vertex_regex(const std::string& type, int mandatory_args, int optional_args)
{
  static const std::string WHITESPACE_REGEX_STRING = "\\s*";
  static const std::string FLOAT_REGEX_STRING = "(([\\+-]?)([0-9]+)(\\.[0-9]+)?([eE]-?[0-9]+)?)";

  std::ostringstream regex_string;
  regex_string << "^";				// beginning of string
  regex_string << WHITESPACE_REGEX_STRING; 	// leading whitespace
  regex_string << type;				// line type
  regex_string << WHITESPACE_REGEX_STRING;
  for (int idx = 0; idx < mandatory_args; idx++)
  {
    regex_string << FLOAT_REGEX_STRING;
    regex_string << WHITESPACE_REGEX_STRING;
  }
  for (int idx = 0; idx < optional_args; idx++)
  {
    regex_string << FLOAT_REGEX_STRING;
    regex_string << "?";
    regex_string << WHITESPACE_REGEX_STRING;
  }
  regex_string << "$";				// end of string

  return std::regex(regex_string.str());
}

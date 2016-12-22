/**
 * @file	wavefront_file.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include <algorithm>
#include <cctype>
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

/* -- Constants -- */

namespace
{
  const std::string FLOAT_REGEX_STRING = "(?:\\s+(?:[+-]?[0-9]+(?:\\.[0-9]+)?(?:[eE]-?[0-9]+)?))";
}

const std::string wavefront_vertex::prefix = "v";
const std::regex wavefront_vertex::regex("^v(" + FLOAT_REGEX_STRING + "{3,4})\\s*$");

const std::string wavefront_normal::prefix = "vn";
const std::regex wavefront_normal::regex("^vn(" + FLOAT_REGEX_STRING + "{3})\\s*$");

const std::string wavefront_face::prefix = "f";
const std::regex wavefront_face::regex("^f((?:\\s+[0-9]+)+)$");

/* -- Procedures -- */

wavefront_vertex::wavefront_vertex(const std::string& line)
{
  std::smatch results;
  if (!std::regex_match(line, results, wavefront_vertex::regex))
    throw file_io_exception("Invalid vertex");

  ogl_dbg_assert(results.size() == 2);
  std::istringstream stream(results[1]);

  stream >> x;
  stream >> y;
  stream >> z;
  if (!(stream >> w))
    w = 1.0f;
}

wavefront_normal::wavefront_normal(const std::string& line)
{
  std::smatch results;
  if (!std::regex_match(line, results, wavefront_normal::regex))
    throw file_io_exception("Invalid normal");

  ogl_dbg_assert(results.size() == 2);
  std::istringstream stream(results[1]);

  stream >> x;
  stream >> y;
  stream >> z;
}

wavefront_face::wavefront_face(const std::string& line)
{
  std::smatch results;
  if (!std::regex_match(line, results, wavefront_face::regex))
    throw file_io_exception("Invalid face");

  ogl_dbg_assert(results.size() == 2);
  std::istringstream stream(results[1]);

  int idx;
  while ((stream >> idx))
    indices.push_back(idx);
}

wavefront_file::wavefront_file(const std::string& filename)
{
    std::fstream infile(filename);
    if (!infile.is_open())
      throw file_io_exception("Unable to open " + filename);

    int line_number = 0;
    std::string line;

    auto is_whitespace = [](char c) { return std::isspace(c); };

    try
    {
      while (std::getline(infile, line))
      {
	++line_number;

	// drop \r from last character, if the file uses windows line endings
	if (line[line.size() - 1] == '\r')
	  line.pop_back();

	// drop comments
	line = line.substr(0, line.find("#"));

	// skip entirely blank lines
	if (line.size() == 0 || std::all_of(line.begin(), line.end(), is_whitespace))
	  continue;

	// check the line type and parse as needed
	if (begins_with(line, wavefront_vertex::prefix))
	  m_vertices.push_back(wavefront_vertex(line));
	else if (begins_with(line, wavefront_normal::prefix))
	  m_normals.push_back(wavefront_normal(line));
	else if (begins_with(line, wavefront_face::prefix))
	  m_faces.push_back(wavefront_face(line));
	else
	{
	  // eventually we will throw here, but for now, just ignore since there's
	  // so much stuff that we don't have implemented
	  // throw file_io_exception("Unknown line format");
	}
      }
    }
    catch (const file_io_exception& ex)
    {
      std::ostringstream message;
      message << "Unable to load " << filename << ". Line " << line_number << " is invalid: " << line;
      throw file_io_exception(message.str());
    }
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
    // NOTE: HAXX
    ogl_dbg_assert(face.indices.size() >= 3);
    auto v1_idx = face.indices[0] - 1;
    auto v2_idx = face.indices[1] - 1;
    auto v3_idx = face.indices[2] - 1;

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

bool wavefront_file::begins_with(const std::string& line, const std::string& prefix)
{
  return (line.size() > prefix.size() + 1 &&
	  line.substr(0, prefix.size()) == prefix &&
	  std::isspace(line[prefix.size()]));
}

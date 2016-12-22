/**
 * @file	wavefront_parser.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/22
 */

/* -- Includes -- */

#include <fstream>
#include <regex>
#include <sstream>
#include <string>

#include "app/wavefront_parser.hpp"
#include "util/debug.hpp"
#include "util/exceptions.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

const std::regex wavefront_parser::comment_regex("#.*$");
const std::regex wavefront_parser::only_whitespace_regex("^\\s*$");
const std::regex wavefront_parser::v_regex = wavefront_parser::vertex_regex("v", 3, 1);
const std::regex wavefront_parser::vt_regex = wavefront_parser::vertex_regex("vt", 2, 1);
const std::regex wavefront_parser::vn_regex = wavefront_parser::vertex_regex("vn", 3, 0);
const std::regex wavefront_parser::f_regex("^\\s*f\\s*([0-9]+)\\s*([0-9]+)\\s*([0-9]+)\\s*$");

/* -- Procedures -- */

void wavefront_parser::parse_file(const std::string& filename,
				  std::vector<glm::vec4>& vertices,
				  std::vector<GLuint>& indices)
{
    std::fstream infile(filename);
    if (!infile.is_open())
      throw file_io_exception("Unable to open " + filename);

    int line_number = 0;
    std::string line;
    while (std::getline(infile, line))
    {
      line_number++;

      // remove comments
      line = std::regex_replace(line, wavefront_parser::comment_regex, "");

      // is the line nothing but whitespace?
      if (std::regex_match(line, wavefront_parser::only_whitespace_regex))
	continue;

      // check for vertices
      std::smatch results;
      if (std::regex_match(line, results, wavefront_parser::v_regex))
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

	vertices.push_back(glm::vec4(x, y, z, w));
	continue;
      }
      else if (std::regex_match(line, results, wavefront_parser::vt_regex))
      {
	static const auto X_INDEX = 1;
	static const auto Y_INDEX = 6;
	static const auto Z_INDEX = 11;

	auto x = std::stof(results[X_INDEX]);
	auto y = std::stof(results[Y_INDEX]);
	auto z = 1.0f;
	if (!results[Z_INDEX].str().empty())
	  z = std::stof(results[Z_INDEX]);

	//std::cout << "Found texture: " << x << " " << y << " " << z << std::endl;
	continue;
      }
      else if (std::regex_match(line, results, wavefront_parser::vn_regex))
      {
	static const auto X_INDEX = 1;
	static const auto Y_INDEX = 6;
	static const auto Z_INDEX = 11;

	auto x = std::stof(results[X_INDEX]);
	auto y = std::stof(results[Y_INDEX]);
	auto z = std::stof(results[Z_INDEX]);

	//std::cout << "Found vertex normal: " << x << " " << y << " " << z << std::endl;
	continue;
      }
      else if (std::regex_match(line, results, wavefront_parser::f_regex))
      {
	static const auto V1_INDEX = 1;
	static const auto V2_INDEX = 2;
	static const auto V3_INDEX = 3;

	auto v1 = std::stoi(results[V1_INDEX]);
	auto v2 = std::stoi(results[V2_INDEX]);
	auto v3 = std::stoi(results[V3_INDEX]);

	indices.push_back(v1);
	indices.push_back(v2);
	indices.push_back(v3);
	continue;
      }

      // if we get to this point, the line is invalid
      std::ostringstream error_msg;
      error_msg << "Invalid line (line " << line_number << "): " << line;
      throw file_io_exception(error_msg.str());
    }
}


std::regex wavefront_parser::vertex_regex(const std::string& type, int mandatory_args, int optional_args)
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
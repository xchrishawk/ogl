/**
 * @file	shaders.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

#pragma once

/* -- Includes -- */

#include <map>
#include <string>

/* -- Constants -- */

namespace ogl
{
  namespace resources
  {

    /** Map of shader filenames to source strings. */
    extern const std::map<std::string, std::string> shader_sources;

  }
}

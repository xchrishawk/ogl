/**
 * @file	resources.hpp
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

    /** Mapping of shader filenames to shader source strings. */
    extern const std::map<std::string, std::string> shader_source_lookup;

  }
}

/**
 * @file	buffer.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/26
 */

#pragma once

/* -- Includes -- */

#include <memory>

/* -- Types -- */

namespace ogl
{

  /**
   * Abstract interface for types representing an OpenGL buffer.
   */
  class buffer
  {
  public:

    /** Shared pointer to a `buffer` instance. */
    typedef std::shared_ptr<buffer> ptr;

    /** Shared pointer to a `const buffer` instance. */
    typedef std::shared_ptr<const buffer> const_ptr;

    virtual ~buffer() { }

  protected:

    buffer() { }

  private:

    buffer(const buffer&) = delete;
    buffer& operator =(const buffer&) = delete;

  };

}

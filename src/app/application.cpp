/**
 * application.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdexcept>

#include "app/application.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Variables -- */

application* application::m_instance;

/* -- Procedures -- */

application::application(const opengl_factory& opengl_fact)
  : m_opengl(opengl_fact.build())
{
  // sanity check - there should only be one instance at a time
  ogl_assert(application::m_instance == nullptr);
  application::m_instance = this;
}

application::~application()
{
  // release the instance pointer
  application::m_instance = nullptr;
}

void application::main()
{
}

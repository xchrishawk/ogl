/**
 * main.cpp
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <cstdlib>
#include <exception>
#include <sstream>
#include <string>

#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>

#include "app/application.hpp"
#include "opengl/opengl.hpp"
#include "util/debug.hpp"

/* -- Namespaces -- */

using namespace ogl;

/* -- Procedures -- */

int main(int argc, char** argv)
{
  try
  {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hi", NULL, NULL);
    while (!glfwWindowShouldClose(window))
      glfwPollEvents();
    glfwDestroyWindow(window);

    // required initialization objects
    opengl_stub_factory opengl_fact;

    // create and run application
    application app(opengl_fact);
    app.main();

    // successful app run!
    return EXIT_SUCCESS;
  }
  catch (const std::exception& ex)
  {
    // print debug info if needed
#if defined(OGL_DEBUG)
    std::ostringstream message;
    message << "Uncaught exception: " << ex.what();
    ogl_fail_message(message.str());
#endif /* defined(OGL_DEBUG) */

    // failed...
    return EXIT_FAILURE;
  }
}

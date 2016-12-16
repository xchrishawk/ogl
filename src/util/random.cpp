/**
 * @file	random.cpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 */

/* -- Includes -- */

#include <cstdlib>
#include <ctime>

#include "util/random.hpp"

/* -- Procedures -- */

void ogl::random_init()
{
  srand(time(NULL));
}

int ogl::random_int()
{
  return rand();
}

int ogl::random_int(int max)
{
  return ogl::random_int() % max;
}

float ogl::random_float()
{
  return static_cast<float>(random_int()) / static_cast<float>(RAND_MAX);
}

float ogl::random_float(float max)
{
  return ogl::random_float() * max;
}

double ogl::random_double()
{
  return static_cast<double>(random_int()) / static_cast<double>(RAND_MAX);
}

double ogl::random_double(double max)
{
  return ogl::random_float() * max;
}

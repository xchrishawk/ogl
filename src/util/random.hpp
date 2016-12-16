/**
 * random.hpp
 * Chris Vig (chris@invictus.so)
 */

#pragma once

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Initializes the random number generator. */
  void random_init();

  /** Returns a random number between 0 and RAND_MAX. */
  int random_int();

  /** Returns a random number between 0 and max. */
  int random_int(int max);

  /** Returns a random float between 0 and 1. */
  float random_float();

  /** Returns a random float between 0 and max. */
  float random_float(float max);

  /** Returns a random double between 0 and 1. */
  double random_double();

  /** Returns a random double between 0 and max. */
  double random_double(double max);

}

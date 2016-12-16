/**
 * @file	random.hpp
 * @author	Chris Vig (chris@invictus.so)
 * @date	2016/12/16
 *
 * Random number generation module.
 */

#pragma once

/* -- Procedure Prototypes -- */

namespace ogl
{

  /** Initializes the random number generator. */
  void random_init();

  /** Returns a random `int` between `0` and `RAND_MAX`. */
  int random_int();

  /** Returns a random `int` between `0` and `max`. */
  int random_int(int max);

  /** Returns a random `float` between `0` and `1`. */
  float random_float();

  /** Returns a random `float` between `0` and `max`. */
  float random_float(float max);

  /** Returns a random `double` between `0` and `1`. */
  double random_double();

  /** Returns a random `double` between `0` and `max`. */
  double random_double(double max);

}

#pragma once
#include "Potential.hpp"
#include "Constants.hpp"

class PotentialHarmonicOscillator : public Potential {
 public:
  inline complex V (long ix, complex t) {
    double x = g->x[ix];
    return complex (0.5 * x * x, 0.);
  }
};

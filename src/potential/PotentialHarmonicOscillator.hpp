#pragma once
#include "Potential.hpp"

class PotentialHarmonicOscillator : public Potential {
 public:
  inline complex V (long ix, long it) {
    double x = g->x[ix];
    return complex (0.5 * x * x, 0.);
  }
};

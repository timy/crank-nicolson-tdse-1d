#pragma once
#include "Potential.hpp"

class PotentialSoftCore : public Potential {
 public:
  double a;
  inline complex V (long ix, complex t) {
    double x = g->x[ix];
    return complex (-1 / sqrt(x*x + a), 0.);
  }
};

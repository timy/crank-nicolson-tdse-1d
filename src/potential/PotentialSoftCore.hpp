#pragma once
#include "Potential.hpp"

class PotentialSoftCore : public Potential {
  complex* pot;

 public:
  double a;

  void Initialize () {
    pot = new complex [g->nx];
    for (int ix = 0; ix < g->nx; ix ++) {
      double x = g->x[ix];
      pot[ix] = complex (-1 / sqrt(x*x + a), 0.);
    }
  }
  void Finalize () {
    delete[] pot;
  }
  inline complex V (long ix, long it) {
    return pot[ix];
  }

};

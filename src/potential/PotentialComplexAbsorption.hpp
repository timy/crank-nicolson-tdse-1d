#pragma once
#include "Potential.hpp"

class PotentialComplexAbsorption : public Potential {
  complex* pot;

 public:
  void Initialize () {
    pot = new complex [g->nx];
    for (int ix = 0; ix < g->nx; ix ++) {
      double x = (double(ix - g->nx/2)) / (g->nx/2);
      double x4 = x*x*x*x;
      pot[ix] = complex (0., -x4*x4*x4*x4);
    }
  }
  void Finalize () {
    delete[] pot;
  }
  inline complex V (long ix, long it) {
    return pot[ix];
  }

};

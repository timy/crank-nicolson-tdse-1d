#pragma once
#include "Potential.hpp"

class PotentialFreeParticle : public Potential {
  complex* pot;

 public:
  void Initialize () {
    pot = new complex [g->nx];
    for (int ix = 0; ix < g->nx; ix ++) {
      pot[ix] = 0.;
    }
  }
  void Finalize () {
    delete[] pot;
  }
  inline complex V (long ix, long it) {
    return pot[ix];
  }

};

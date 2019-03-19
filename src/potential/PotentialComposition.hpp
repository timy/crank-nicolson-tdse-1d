#pragma once
#include "Potential.hpp"

class PotentialComposition : public Potential {
 public:
  int np;
  Potential** pot;

  void Initialize () {
    for (int i = 0; i < np; i ++)
      pot[i]->Initialize ();
  }
  void Initialize (int n) {
    np = n;
    pot = new Potential* [np];
  }
  void Finalize () {
    for (int i = 0; i < np; i ++)
      pot[i]->Finalize ();
    delete [] pot;
  }

  void setup_grid (Grid* grid) {
    for (int i = 0; i < np; i ++) {
      pot[i]->setup_grid (grid);
    }
    Potential::setup_grid (grid);
  }

  void setup_file (const char* dir) {
    for (int i = 0; i < np; i ++) {
      pot[i]->setup_file (dir);
    }
    Potential::setup_file (dir);
  }

  inline complex V (long ix, long it) {
    complex s = 0.;
    for (int i = 0; i < np; i ++) {
      s += pot[i]->V (ix, it);
    }
    return s;
  }


};

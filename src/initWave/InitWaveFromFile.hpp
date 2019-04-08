#pragma once
#include "InitWave.hpp"

class InitWaveFromFile : public InitWave {
 public:
  complex* wf;
  char filename[512];

  int Initialize (Grid *grid) {
    g = grid;
    FILE* file = fopen (filename, "r");
    wf = new complex [g->nx];
    double re, im;
    for (long i = 0; i < g->nx; i ++) {
      fscanf (file, "%le %le ", &re, &im);
      wf[i] = complex (re, im);
    }
    fclose (file);
  }

  void Finalize () {
    delete[] wf;
  }

  inline complex operator () (long ix) {
    return wf[ix];
  }
};

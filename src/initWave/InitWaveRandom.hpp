#pragma once
#include "InitWave.hpp"

class InitWaveRandom : public InitWave {
 public:
  inline complex operator () (long ix) {
    return rand ();
  }
};

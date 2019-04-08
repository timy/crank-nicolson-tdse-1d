#pragma once

#include "Constants.hpp"

class Grid;
class InitWave {
 public:
  Grid *g;

  InitWave () {};
  virtual ~InitWave () {};

  virtual int Initialize (Grid *grid);
  virtual void Finalize ();
  virtual complex operator () (long i) = 0;
};

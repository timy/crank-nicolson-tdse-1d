#pragma once

class Grid;
class InitWave {
 public:
  Grid *g;

  InitWave () {};
  virtual ~InitWave () {};

  virtual complex operator () (long i) = 0;
};

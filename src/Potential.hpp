#pragma once
#include "Grid.hpp"
#include "Constants.hpp"
#include <cstdio>

class Potential {
 public:
  Grid *g;
  Files files;

  Potential () {};
  virtual ~Potential () {};

  virtual void Initialize () {}
  virtual void Finalize () {}

  // Example:  return 0.01 * x * x + sin(0.2 * t) * x;
  virtual complex V (long ix, long it) = 0;

  virtual void setup_grid (Grid* grid) {
    g = grid;
  }

  virtual void setup_file (const char* dir) {
    files.set_dir (dir);
    files.open ("pot", "w");
  }

  virtual void dump_to_file (long it) {
    for (int ix = 0; ix < g->nx; ix ++) {
      fprintf(files[0], "%le ", real(V(ix, it)));
    }
    fprintf(files[0], "\n");
  }
};

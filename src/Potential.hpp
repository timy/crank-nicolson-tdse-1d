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

  // Example:  return 0.01 * x * x + sin(0.2 * t) * x;
  virtual complex V (long x, complex t) = 0;

  void setup_file (const char* dir) {
    files.set_dir (dir);
    files.open ("pot", "w");
  }

  void dump_to_file (complex t) {
    for (int ix = 0; ix < g->nx; ix ++) {
      fprintf(files[0], "%le ", real(V(ix, t)));
    }
    fprintf(files[0], "\n");
  }
};

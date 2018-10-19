#pragma once
#include "Grid.hpp"
#include "Constants.hpp"
#include <cstdio>

class Potential {
 public:
  Grid *g;

  Potential () {};
  virtual ~Potential () {};

  // Example:  return 0.01 * x * x + sin(0.2 * t) * x;
  virtual complex V (long x, complex t) = 0;

  void dump_to_file (FILE* file, complex t) {
    for (int ix = 0; ix < g->nx; ix ++) {
      fprintf(file, "%le ", real(V(ix, t)));
    }
    fprintf(file, "\n");
  }
};

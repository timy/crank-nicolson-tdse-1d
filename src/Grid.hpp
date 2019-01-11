#pragma once
#include <cstdio>
#include "Files.hpp"

class Grid {
 public:
  int nx;
  double dx, x0;
  double* x;
  Files files;

  Grid (int nx_, double dx_, double x0_): nx (nx_), dx (dx_), x0 (x0_) {
    x = new double [nx];
    for (int ix = 0; ix < nx; ix ++)
      x[ix] = x0 + ix * dx;
    files.open ("grid", "w");
    this->dump_to_file ();
  }
  ~Grid () {
    delete[] x;
  }
  void dump_to_file () {
    for (int ix = 0; ix < nx; ix ++)
      fprintf (files[0], "%lf\n", x[ix]);
  }
};

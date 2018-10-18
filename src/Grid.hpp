#pragma once
#include <cstdio>

class Grid {
 public:
  int nx;
  double dx, x0;
  double* x;

  Grid (int nx_, double dx_, double x0_): nx (nx_), dx (dx_), x0 (x0_) {
    x = new double [nx];
    for (int ix = 0; ix < nx; ix ++)
      x[ix] = x0 + ix * dx;
  }
  ~Grid () {
    delete[] x;
  }
  void dump_to_file (FILE* file) {
    for (int ix = 0; ix < nx; ix ++)
      fprintf (file, "%lf\n", x[ix]);
  }
};

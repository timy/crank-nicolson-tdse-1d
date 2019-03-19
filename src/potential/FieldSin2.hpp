#pragma once
#include "Potential.hpp"

class FieldSin2 : public Potential {
  double* Ef;
  Files files;

 public:

  long nt;
  long print_steps;
  double dt;
  double w;
  double nc;
  double E0;

  void setup_file (const char* dir) {
    files.set_dir (dir);
    files.open ("field", "w");
  }

  void dump_to_file () {
    for (long it = 0; it <= nt; it ++) {
      if (it % print_steps == 0) {
        fprintf (files[0], "%le\n", Ef[it]);
      }
    }
  }

  void Initialize () {
    Ef = new double [nt+1];
    double duration = 2.* M_PI * nc / w;
    for (long it = 0; it <= nt; it ++) {
      double t = it * dt;
      double env = 0.;
      if (t < duration)
        env = sin (w*t/(2.*nc));
      Ef[it] = - E0 * env * env * sin (w*t);
    }
    this->dump_to_file ();
  }

  void Finalize () {
    delete[] Ef;
  }

  inline complex V (long ix, long it) {
    double x = g->x[ix];
    return complex (Ef[it]) * x;
  }

};

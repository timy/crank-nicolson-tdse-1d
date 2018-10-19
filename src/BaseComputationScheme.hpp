#pragma once

#include "IComputationScheme.hpp"
#include "Constants.hpp"

class Grid;
class Potential;
class Files;
class Wavefunc;
class InitWave;

namespace CNTDSE1D {

class BaseComputationScheme : public IComputationScheme {
 public:

  long      nx;
  double    x0;
  double    dx;

  long      nt;
  double    dt;

  long      print_steps;

  complex   time_step;
  Grid      *g;
  Potential *pot;
  InitWave  *initWave;
  Wavefunc  *wf;
  Files     *files;

  virtual int Initialize ();
  virtual int Run ();
  virtual void Finalize ();
};

}

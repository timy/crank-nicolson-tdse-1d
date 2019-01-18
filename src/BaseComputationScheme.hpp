#pragma once

#include "IComputationScheme.hpp"
#include "Constants.hpp"

class Grid;
class Potential;
class Wavefunc;
class InitWave;

namespace CNTDSE1D {

class BaseComputationScheme : public IComputationScheme {
 public:

  long      nx;          // explicit input required
  double    x0;          // explicit input required
  double    dx;          // explicit input required

  long      nt;          // explicit input required
  double    dt;          // explicit input required

  long      print_steps; // explicit input required

  complex   time_step;
  Grid      *g;
  Potential *pot;        // explicit input required
  Wavefunc  *wf;

  char base_dir[128];

  virtual int Initialize ();
  virtual int InitWaveFunc (InitWave* initWave);
  virtual int Run ();
  virtual void Finalize ();
};

}

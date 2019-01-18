#include "Grid.hpp"
#include "Potential.hpp"
#include "Wavefunc.hpp"

#include "BaseComputationScheme.hpp"
#include <cstdio>

int CNTDSE1D::BaseComputationScheme::Initialize () {
  printf ("start initialization!\n");

  // setup grid
  g = new Grid (nx, dx, x0);
  g->setup_file (base_dir);
  g->dump_to_file ();
  pot->g = g;
  pot->setup_file (base_dir);
  return 0;
}

int CNTDSE1D::BaseComputationScheme::InitWaveFunc (InitWave* initWave) {
  // initialize wave function
  initWave->g = g;
  wf = new Wavefunc (*g, *pot, time_step);
  wf->init (initWave);
  return 0;
}

int CNTDSE1D::BaseComputationScheme::Run () {
}

void CNTDSE1D::BaseComputationScheme::Finalize () {
  delete wf;
  delete g;
}

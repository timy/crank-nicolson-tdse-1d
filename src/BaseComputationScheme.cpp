#include "Grid.hpp"
#include "Potential.hpp"
#include "Files.hpp"
#include "Wavefunc.hpp"

#include "BaseComputationScheme.hpp"
#include <cstdio>

int CNTDSE1D::BaseComputationScheme::Initialize () {
  printf ("start initialization!\n");

  files = new Files;

  // setup grid
  g = new Grid (nx, dx, x0);
  g->dump_to_file (files->grid);
  pot->g = g;
  initWave->g = g;

  // initialize wave function
  wf = new Wavefunc (*g, *pot, time_step);
  wf->init (initWave);

  return 0;
}

int CNTDSE1D::BaseComputationScheme::Run () {
}

void CNTDSE1D::BaseComputationScheme::Finalize () {
  delete wf;
  delete files;
  delete g;
}

#include "Grid.hpp"
#include "Potential.hpp"
#include "Files.hpp"
#include "Wavefunc.hpp"
#include "InitWave.hpp"

#include "BaseComputationScheme.hpp"
#include <cstdio>

#define I complex(0., 1.)

int CNTDSE1D::BaseComputationScheme::Initialize () {
  printf ("start initialization!\n");

  g = new Grid (nx, dx, x0);
  pot->g = g;
  initWave->g = g;

  files = new Files;

  g->dump_to_file (files->grid);

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

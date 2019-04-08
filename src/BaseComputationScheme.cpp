#include "Grid.hpp"
#include "Potential.hpp"
#include "Wavefunc.hpp"

#include "BaseComputationScheme.hpp"
#include <iostream>

int CNTDSE1D::BaseComputationScheme::Initialize () {
  std::cout << "START: BaseComputationScheme::Initialize" << std::endl;
  // setup grid
  g = new Grid (nx, dx, x0);
  g->setup_file (base_dir);
  g->dump_to_file ();
  pot->setup_grid (g);
  pot->setup_file (base_dir);
  pot->Initialize ();
  wf = new Wavefunc (*g, *pot, time_step);
  std::cout << "  END: BaseComputationScheme::Initialize" << std::endl;
  return 0;
}

void CNTDSE1D::BaseComputationScheme::Finalize () {
  std::cout << "START: BaseComputationScheme::Finalize" << std::endl;
  pot->Finalize ();
  delete wf;
  delete g;
  std::cout << "  END: BaseComputationScheme::Finalize" << std::endl;
}

int CNTDSE1D::BaseComputationScheme::Run () {
  std::cout << "START: BaseComputationScheme::Run" << std::endl;
  std::cout << "  END: BaseComputationScheme::Run" << std::endl;
  return 0;
}

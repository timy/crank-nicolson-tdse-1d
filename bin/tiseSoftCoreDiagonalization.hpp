#pragma once

#include "TISEExactDiagonalization.hpp"
#include "potential/PotentialSoftCore.hpp"
#include "initWave/InitWaveRandom.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TISEExactDiagonalization {

  PotentialSoftCore pot_soft_core;

 public:

  int Initialize () {

    ns = 20;     // number of states

    nx = 801; //8001 // number of spatial grid points
    x0 = -40; //-160;   // starting position
    dx = 0.1; //0.04;  // spatial step size

    nt = 100;  // number of time steps
    dt = 0.2; //0.02;  // time interval

    print_steps = 10; // output results every print_steps

    pot_soft_core.a = 2.; // parameter of soft core potential
    // Examples:
    // when a = 2.0, E_0 = 13.6 eV
    // when a = 1.0, E_0 = 18.2 eV
    // when a = 0.4, E_0 = 26.5 eV

    pot = &pot_soft_core;  // potential

    strcpy (base_dir, "res_im"); // directory to store results

    return TISEExactDiagonalization::Initialize ();
  }
};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

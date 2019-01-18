#pragma once

#include "TISEComputationScheme.hpp"
#include "potential/PotentialHarmonicOscillator.hpp"
#include "initWave/InitWaveRandom.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TISEComputationScheme {

  PotentialHarmonicOscillator pot_harmonic_oscillator;

 public:

  int Initialize () {

    ns = 3;     // number of states

    nx = 2001;  // number of spatial grid points
    x0 = -40;   // starting position
    dx = 0.04;  // spatial step size

    nt = 4000;  // number of time steps
    dt = 0.02;  // time interval

    print_steps = 20; // output results every print_steps

    pot = &pot_harmonic_oscillator; // potential

    strcpy (base_dir, "res_im"); // directory to store results

    return TISEComputationScheme::Initialize ();
  }

  int InitWaveFunc () {
    InitWaveRandom random_wf;
    return TISEComputationScheme::InitWaveFunc (&random_wf);
  }

};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

#pragma once

#include "TISEImaginaryTimeProp.hpp"
#include "potential/PotentialHarmonicOscillator.hpp"
#include "initWave/InitWaveRandom.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TISEImaginaryTimeProp {

  PotentialHarmonicOscillator pot_harmonic_oscillator;
  InitWaveRandom random_wf;

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
    initWave = &random_wf; // initial wavefunction

    strcpy (base_dir, "res_im"); // directory to store results

    return TISEImaginaryTimeProp::Initialize ();
  }
};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

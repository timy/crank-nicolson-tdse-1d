#pragma once

#include "TDSEComputationScheme.hpp"
#include "potential/PotentialHarmonicOscillator.hpp"
#include "initWave/InitWaveGaussian.hpp"
#include "initWave/InitWaveFromFile.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TDSEComputationScheme {

  PotentialHarmonicOscillator pot_harmonic_oscillator;
  InitWaveGaussian gaussian;
  // InitWaveFromFile wfFromFile;

 public:

  int Initialize () {

    nx = 2001;
    x0 = -40;
    dx = 0.04;

    nt = 4000;
    dt = 0.02;

    print_steps = 20;

    pot = &pot_harmonic_oscillator;

    // initial wavefunction: gaussian
    gaussian.x0 = -20.;
    gaussian.sigma = 1.;
    gaussian.k = 4.;
    initWave = &gaussian;

    // // initial wavefunction: read from file
    // strcpy (wfFromFile.filename, "res_im/wf_1.dat");
    // initWave = &wfFromFile;

    strcpy (base_dir, "res_re"); // directory to store results

    return TDSEComputationScheme::Initialize ();
  }
};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

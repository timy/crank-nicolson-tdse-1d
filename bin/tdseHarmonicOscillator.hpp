#pragma once

#include "TDSEComputationScheme.hpp"
#include "potential/PotentialHarmonicOscillator.hpp"
// #include "initWave/InitWaveGaussian.hpp"
#include "initWave/InitWaveFromFile.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TDSEComputationScheme {

  PotentialHarmonicOscillator pot_harmonic_oscillator;

 public:

  int Initialize () {

    nx = 2001;
    x0 = -40;
    dx = 0.04;

    nt = 4000;
    dt = 0.02;

    print_steps = 20;

    pot = &pot_harmonic_oscillator;

    return TDSEComputationScheme::Initialize ();
  }

  int InitWaveFunc () {
    // // Gaussian
    // InitWaveGaussian gaussian;
    // gaussian.x0 = -20.;
    // gaussian.sigma = 1.;
    // gaussian.k = 4.;
    // return TDSEComputationScheme::InitWaveFunc (&gaussian);

    // read from file
    InitWaveFromFile wfFromFile ("res/wf_init_1.dat", g);
    return TDSEComputationScheme::InitWaveFunc (&wfFromFile);
  }
};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

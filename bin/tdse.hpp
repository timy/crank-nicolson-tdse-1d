#pragma once

#include "TDSEComputationScheme.hpp"
#include "potential/PotentialHarmonicOscillator.hpp"
#include "initWave/InitWaveGaussian.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TDSEComputationScheme {

  PotentialHarmonicOscillator pot_harmonic_oscillator;
  InitWaveGaussian gaussian;

 public:

  int Initialize () {

    nx = 2001;
    x0 = -40;
    dx = 0.04;

    nt = 4000;
    dt = 0.02;
    pot = &pot_harmonic_oscillator;

    print_steps = 20;

    gaussian.x0 = -20.;
    gaussian.sigma = 1.;
    gaussian.k = 4.;
    initWave = &gaussian;

    return TDSEComputationScheme::Initialize ();
  }

};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

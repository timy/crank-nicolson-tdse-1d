#pragma once

#include "TDSEComputationScheme.hpp"
#include "potential/PotentialComposition.hpp"
#include "potential/PotentialFreeParticle.hpp"
#include "potential/PotentialComplexAbsorption.hpp"
#include "initWave/InitWaveGaussian.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TDSEComputationScheme {

  PotentialComposition pot_composition;
  PotentialFreeParticle pot_free_particle;
  PotentialComplexAbsorption pot_imag_absorb;
  InitWaveGaussian gaussian;

 public:

  int Initialize () {

    nx = 2001;
    x0 = 0.;
    dx = 0.1;

    nt = 4000;
    dt = 0.02;

    print_steps = 20;

    pot_composition.Initialize(2);
    pot_composition.pot[0] = &pot_free_particle;
    pot_composition.pot[1] = &pot_imag_absorb;
    pot = &pot_composition;

    gaussian.x0 = 50.;
    gaussian.sigma = 1.;// 1.;
    gaussian.k = 4.;
    initWave = &gaussian;

    strcpy (base_dir, "res_re"); // directory to store results

    return TDSEComputationScheme::Initialize ();
  }
};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

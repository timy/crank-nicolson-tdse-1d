#pragma once

#include "TDSEComputationScheme.hpp"
#include "potential/PotentialComposition.hpp"
#include "potential/PotentialSoftCore.hpp"
#include "potential/PotentialComplexAbsorption.hpp"
#include "potential/FieldSin2.hpp"
#include "initWave/InitWaveGaussian.hpp"
#include "initWave/InitWaveFromFile.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TDSEComputationScheme {

  PotentialComposition pot_composition;
  PotentialSoftCore pot_soft_core;
  FieldSin2 field_sin2;
  PotentialComplexAbsorption pot_imag_absorb;
  // InitWaveGaussian gaussian;
  InitWaveFromFile wfFromFile;

 public:

  int Initialize () {

    nx = 4001;
    x0 = -200; //-160;
    dx = 0.1; //0.04;

    nt = 60000; //20000;
    dt = 0.02;

    print_steps = 100;

    pot_soft_core.a = 2.;

    field_sin2.nt = nt;
    field_sin2.print_steps = print_steps;
    field_sin2.dt = dt;
    field_sin2.w = 0.169;
    field_sin2.nc = 24.;
    field_sin2.E0 = 0.0534;

    pot_composition.Initialize(3);
    pot_composition.pot[0] = &pot_soft_core;
    pot_composition.pot[1] = &field_sin2;
    pot_composition.pot[2] = &pot_imag_absorb;
    pot = &pot_composition;

    // // Gaussian
    // InitWaveGaussian gaussian;
    // gaussian.x0 = 0.; //-20.;
    // gaussian.sigma = 0.1;// 1.;
    // gaussian.k = 4.;
    // initWave = &gaussian;

    // initial wavefunction: read from file
    strcpy (wfFromFile.filename, "res_im/wf_0.dat");
    initWave = &wfFromFile;

    strcpy (base_dir, "res_re"); // directory to store results

    return TDSEComputationScheme::Initialize ();
  }
};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

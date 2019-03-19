#pragma once

#include "TDSEComputationScheme.hpp"
#include "potential/PotentialComposition.hpp"
#include "potential/PotentialSoftCore.hpp"
#include "potential/FieldSin2.hpp"
#include "initWave/InitWaveGaussian.hpp"
#include "initWave/InitWaveFromFile.hpp"

namespace CNTDSE1D {
class MyComputationScheme : public TDSEComputationScheme {

  PotentialComposition pot_composition;
  PotentialSoftCore pot_soft_core;
  FieldSin2 field_sin2;

 public:

  int Initialize () {

    nx = 8001;
    x0 = -160;
    dx = 0.04;

    nt = 8000;
    dt = 0.02;

    print_steps = 50;

    pot_soft_core.a = 2.;

    field_sin2.nt = nt;
    field_sin2.print_steps = print_steps;
    field_sin2.dt = dt;
    field_sin2.w = 0.169;
    field_sin2.nc = 3.;
    field_sin2.E0 = 0.0534;

    pot_composition.Initialize(2);
    pot_composition.pot[0] = &pot_soft_core;
    pot_composition.pot[1] = &field_sin2;
    pot = &pot_composition;

    strcpy (base_dir, "res_re"); // directory to store results

    return TDSEComputationScheme::Initialize ();
  }

  int InitWaveFunc () {
    // // Gaussian
    // InitWaveGaussian gaussian;
    // gaussian.x0 = 0.; //-20.;
    // gaussian.sigma = 0.1;// 1.;
    // gaussian.k = 4.;
    // return TDSEComputationScheme::InitWaveFunc (&gaussian);

    // read from file
    InitWaveFromFile wfFromFile ("res_im/wf_0.dat", g);
    return TDSEComputationScheme::InitWaveFunc (&wfFromFile);
  }
};

MyComputationScheme scheme;
IComputationScheme* g_pScheme = &scheme;
}

#include "TDSEComputationScheme.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"

int CNTDSE1D::TDSEComputationScheme::Initialize () {
  time_step = dt;
  return BaseComputationScheme::Initialize ();
}

int CNTDSE1D::TDSEComputationScheme::InitWaveFunc (InitWave* initWave) {
  return BaseComputationScheme::InitWaveFunc (initWave);
}

int CNTDSE1D::TDSEComputationScheme::Run () {
  double t = 0.;
  Files files_time   (  "time", "w", base_dir, 1);
  Files files_energy ("energy", "w", base_dir, 1);
  Files files_norm   (  "norm", "w", base_dir, 1);
  Files files_wf     (    "wf", "w", base_dir, 1);
  Files files_x      (     "x", "w", base_dir, 1);
  Files files_p      (     "p", "w", base_dir, 1);

  auto dump_info_to_file = [&] (long it) {
    fprintf (files_time[0], "%lf\n", t);
    wf->dump_norm_to_file (files_norm[0]);
    wf->dump_wf_to_file (files_wf[0]);
    pot->dump_to_file (it);
    double energy = wf->energy ();
    fprintf (files_energy[0], "%le\n", energy);
    double x = wf->expect_x ();
    fprintf (files_x[0], "%le\n", x);
    double p = wf->expect_p ();
    fprintf (files_p[0], "%le\n", p);
    printf ("step:%ld\tnorm:%le energy:%le\n", it, wf->norm(), energy);
  };

  for (long it = 0; it < nt; it ++) {
    if (it % print_steps == 0) {
      dump_info_to_file (it);
    }
    wf->propagate (it);
    t += dt;
  }
  dump_info_to_file (nt);

  return 0;
}

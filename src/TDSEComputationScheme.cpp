#include "TDSEComputationScheme.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"

int CNTDSE1D::TDSEComputationScheme::Initialize () {
  time_step = dt;
  return BaseComputationScheme::Initialize ();
}

int CNTDSE1D::TDSEComputationScheme::Run () {
  double t = 0.;
  Files files_time ("time", "w");
  Files files_energy ("energy", "w");
  Files files_norm ("norm", "w");
  Files files_wf ("wf", "w");

  auto dump_info_to_file = [&] (long it) {
    fprintf (files_time[0], "%lf\n", t);
    wf->dump_norm_to_file (files_norm[0]);
    wf->dump_wf_to_file (files_wf[0]);
    pot->dump_to_file (t);
    double energy = wf->energy ();
    fprintf (files_energy[0], "%le\n", energy);
    printf ("step:%ld\tnorm:%le energy:%le\n", it, wf->norm(), energy);
  };

  for (long it = 0; it < nt; it ++) {
    if (it % print_steps == 0) {
      dump_info_to_file (it);
    }
    wf->propagate (t);
    t += dt;
  }
  dump_info_to_file (nt);

  return 0;
}

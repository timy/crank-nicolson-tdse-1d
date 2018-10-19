#include "TDSEComputationScheme.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"

int CNTDSE1D::TDSEComputationScheme::Initialize () {
  time_step = dt;
  return BaseComputationScheme::Initialize ();
}

int CNTDSE1D::TDSEComputationScheme::Run () {
  double t = 0.;
  for (long it = 0; it < nt; it ++) {
    if (it % print_steps == 0) {
      fprintf (files->time, "%lf\n", t);
      wf->dump_to_file (files->norm);
      pot->dump_to_file (files->pot, t);
      printf ("step:%ld\tnorm:%le energy:%le\n", it, wf->norm(), wf->energy());
    }
    wf->propagate (t);
    t += dt;
  }
  // print for the last step
  fprintf (files->time, "%lf\n", t);
  wf->dump_to_file (files->norm);
  pot->dump_to_file (files->pot, t);
  printf ("step:%ld\tnorm:%le energy:%le\n", nt, wf->norm(), wf->energy());

  return 0;
}

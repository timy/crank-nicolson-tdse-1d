#include "TISEComputationScheme.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"

int CNTDSE1D::TISEComputationScheme::Initialize () {
  time_step = -I * dt;
  return BaseComputationScheme::Initialize ();
}

int CNTDSE1D::TISEComputationScheme::Run () {
  // Calculate ground state by imaginary time propagation
  // Excited states are obtained by Gram-Schmidt orthogonalization

  Files files_time   ("time"  , "w");
  Files files_energy ("energy", "w", ns);
  Files files_norm   ("norm"  , "w", ns);

  complex* psi_init = new complex [g->nx];
  for (int ix = 0; ix < g->nx; ix ++)
    psi_init[ix] = wf->psi[ix];

  complex** psi = new complex* [ns];
  for (int is = 0; is < ns; is ++)
    psi[is] = new complex [g->nx];

  pot->dump_to_file (0.);

  complex t;
  auto dump_info_to_file = [&] (int is, long it) {
    if (is == 0)
      fprintf (files_time[0], "%lf\n", abs (t));
    wf->dump_to_file (files_norm[is]);
    double energy = wf->energy ();
    fprintf (files_energy[is], "%le\n", energy);
    printf ("step:%ld time:(%f %f) \tnorm:%le energy:%le\n",
            it, real (t), imag (t), wf->norm (), energy);
  };

  // start propagation
  for (int is = 0; is < ns; is ++) {
    for (int ix = 0; ix < g->nx; ix ++)
      wf->psi[ix] = psi_init[ix];
    t = 0.;
    for (long it = 0; it < nt; it ++) {
      // only output the convergence check for the highest energy state desired

      if (it % print_steps == 0) {
        dump_info_to_file (is, it);
      }

      for (int is1 = 0; is1 < is; is1 ++)
        wf->orthogonalize (psi[is1]);
      wf->propagate (t);
      wf->normalize (); // used for imaginary time propagation
      t += wf->dt;
    }
    for (int ix = 0; ix < g->nx; ix ++)
      psi[is][ix] = wf->psi[ix];
    dump_info_to_file (is, nt);
  }
  for (int is = 0; is < ns; is ++)
    delete[] psi[is];
  delete[] psi_init;

  return 0;
}

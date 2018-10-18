#include "TISEComputationScheme.hpp"
#include "Constants.hpp"
#include "Grid.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"

int CNTDSE1D::TISEComputationScheme::Initialize () {
  time_step = -I * dt;
  return BaseComputationScheme::Initialize ();
}

int CNTDSE1D::TISEComputationScheme::Run () {
  // Calculate ground state by imaginary time propagation
  // Excited states are obtained by Gram-Schmidt orthogonalization

  complex* psi_init = new complex [g->nx];
  for (int ix = 0; ix < g->nx; ix ++)
    psi_init[ix] = wf->psi[ix];

  complex** psi = new complex* [ns];
  for (int is = 0; is < ns; is ++)
    psi[is] = new complex [g->nx];

  // start propagation
  for (int is = 0; is < ns; is ++) {
    for (int ix = 0; ix < g->nx; ix ++)
      wf->psi[ix] = psi_init[ix];
    complex t = 0.;
    for (long it = 0; it < nt; it ++) {
      // only output the convergence check for the highest energy state desired
      if (is == ns-1) {
        if (it % print_steps == 0) {
          fprintf (files->time, "%lf\n", abs (t));
          wf->dump_to_file (files->norm);
          printf ("step:%ld time:(%f %f) \tnorm:%le energy:%le\n",
                  it, real (t), imag (t), wf->norm (), wf->energy ());
        }
      }

      for (int is1 = 0; is1 < is; is1 ++)
        wf->orthogonalize (psi[is1]);
      wf->propagate (t);
      wf->normalize (); // used for imaginary time propagation
      t += wf->dt;
    }
    for (int ix = 0; ix < g->nx; ix ++)
      psi[is][ix] = wf->psi[ix];

    printf ("Energy of state %d: %le\n", is, wf->energy ());
    // output...
    if (is == ns-1) {
      fprintf (files->time, "%lf\n", abs (t));
      wf->dump_to_file (files->norm);
      printf ("step:%ld time:(%f %f) \tnorm:%le energy:%le\n",
              nt, real (t), imag (t), wf->norm (), wf->energy ());
    }

  }
  for (int is = 0; is < ns; is ++)
    delete[] psi[is];
  delete[] psi_init;

  return 0;
}

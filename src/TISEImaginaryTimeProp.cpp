#include "TISEImaginaryTimeProp.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"
#include <fstream>
#include <iostream>

int CNTDSE1D::TISEImaginaryTimeProp::Initialize () {
  std::cout << "START: TISEImaginaryTimeProp::Initialize" << std::endl;
  time_step = -I * dt;
  TISEComputationScheme::Initialize (); // setup grid, pot and prepare wf
  initWave->Initialize (g);
  wf->init (initWave);
  std::cout << "  END: TISEImaginaryTimeProp::Initialize" << std::endl;
  return 0;
}

void CNTDSE1D::TISEImaginaryTimeProp::Finalize () {
  std::cout << "START: TISEImaginaryTimeProp::Finalize" << std::endl;
  initWave->Finalize ();
  std::cout << "  END: TISEImaginaryTimeProp::Finalize" << std::endl;
  BaseComputationScheme::Finalize ();
}

int CNTDSE1D::TISEImaginaryTimeProp::Run () {
  // Calculate ground state by imaginary time propagation
  // Excited states are obtained by Gram-Schmidt orthogonalization
  std::cout << "START: TISEImaginaryTimeProp::Run" << std::endl;
  Files files_time   (  "time", "w", base_dir,  1);
  Files files_energy ("energy", "w", base_dir, ns);
  Files files_norm   (  "norm", "w", base_dir, ns);
  Files files_wf     (    "wf", "w", base_dir, ns);

  complex* psi_init = new complex [g->nx];
  for (int ix = 0; ix < g->nx; ix ++)
    psi_init[ix] = wf->psi[ix];

  complex** psi = new complex* [ns];
  for (int is = 0; is < ns; is ++)
    psi[is] = new complex [g->nx];

  pot->dump_to_file (0);

  complex t;
  auto dump_info_to_file = [&] (int is, long it) {
    if (is == 0)
      fprintf (files_time[0], "%lf\n", abs (t));
    wf->dump_norm_to_file (files_norm[is]);
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
      wf->propagate (it);
      wf->normalize (); // used for imaginary time propagation
      t += wf->dt;
    }
    for (int ix = 0; ix < g->nx; ix ++)
      psi[is][ix] = wf->psi[ix];
    dump_info_to_file (is, nt);
    wf->dump_wf_to_file (files_wf[is]);
  }
  for (int is = 0; is < ns; is ++)
    delete[] psi[is];
  delete[] psi;
  delete[] psi_init;

  std::cout << "  END: TISEImaginaryTimeProp::Run" << std::endl;
  return 0;
}

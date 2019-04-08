#include "TISEExactDiagonalization.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"
#include <fstream>
#include <iostream>

int CNTDSE1D::TISEExactDiagonalization::Initialize () {
  TISEComputationScheme::Initialize ();
  std::cout << "START: TISEExactDiagonalization::Initialize" << std::endl;
  hamil_d = new double [nx];
  hamil_e = new double [nx-1];
  hamil_work = new double [2*nx-2];
  hamil_z = new complex [nx*nx];
  std::cout << "  END: TISEExactDiagonalization::Initialize" << std::endl;
  return 0;
}

void CNTDSE1D::TISEExactDiagonalization::Finalize () {
  std::cout << "START: TISEExactDiagonalization::Finalize" << std::endl;
  delete[] hamil_d;
  delete[] hamil_e;
  delete[] hamil_work;
  delete[] hamil_z;
  std::cout << "  END: TISEExactDiagonalization::Finalize" << std::endl;
  TISEComputationScheme::Finalize ();
}

int CNTDSE1D::TISEExactDiagonalization::Run () {
  // Calculate eigen-states by exact diagonalization of Hamiltonian
  std::cout << "START: TISEExactDiagonalization::Run" << std::endl;

  Files files_time   (  "time", "w", base_dir,  1);
  Files files_energy ("energy", "w", base_dir, ns);
  Files files_norm   (  "norm", "w", base_dir, ns);
  Files files_wf     (    "wf", "w", base_dir, ns);

  char compz = 'I';
  double tmp = 1. / (dx*dx);
  for (long ix = 0; ix < nx; ix ++)
    hamil_d[ix] = tmp + real (pot->V (ix, 0));
  for (long ix = 0; ix < nx-1; ix ++)
    hamil_e[ix] = -0.5 * tmp;
  int ldz = (int)nx, n = (int)nx, info = 0;
  zsteqr_ (&compz, &n, hamil_d, hamil_e, hamil_z,
           &ldz, hamil_work, &info);

  if (info == 0) {
    auto dump_info_to_file = [&] (int is) {
      if (is == 0)
        fprintf (files_time[0], "%lf\n", 0.);
      wf->dump_norm_to_file (files_norm[is]);
      wf->dump_wf_to_file (files_wf[is]);
      fprintf (files_energy[is], "%le\n", hamil_d[is]);
      std::cout << "state " << is << ": " << hamil_d[is] << std::endl;
    };

    std::cout << "State" << "     " << "Energy" << std::endl;
    for (int is = 0; is < ns; is ++) {
      for (long ix = 0; ix < nx; ix ++)
        wf->psi[ix] = hamil_z[is*nx + ix];
      wf->normalize ();
      dump_info_to_file (is);
    }
    pot->dump_to_file (0);
  } else {
    std::cerr << "ERROR: zsteqr_ info = " << info << std::endl;
  }

  std::cout << "  END: TISEExactDiagonalization::Run" << std::endl;
  return 0;
}

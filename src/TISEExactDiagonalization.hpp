#include "TISEComputationScheme.hpp"

namespace CNTDSE1D {

class TISEExactDiagonalization : public TISEComputationScheme {
  double *hamil_d, *hamil_e, *hamil_work;
  complex *hamil_z;

 public:

  int Initialize ();
  void Finalize ();
  int Run ();
};

}

extern "C" {
  extern int zsteqr_(char* COMPZ, int* N, double* D, double* E,
                     complex* Z, int* LDZ, double* WORK,
                     int* INFO);
}

#include "TISEComputationScheme.hpp"

namespace CNTDSE1D {

class TISEImaginaryTimeProp : public TISEComputationScheme {
 public:
  InitWave* initWave;

  int Initialize ();
  void Finalize ();
  int Run ();
};

}

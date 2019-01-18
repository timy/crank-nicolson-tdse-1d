#include "BaseComputationScheme.hpp"

namespace CNTDSE1D {

class TISEComputationScheme : public BaseComputationScheme {
 public:

  int ns = 1;

  int Initialize ();
  int InitWaveFunc (InitWave* initWave);
  int Run ();
};

}

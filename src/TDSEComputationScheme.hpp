#include "BaseComputationScheme.hpp"

namespace CNTDSE1D {

class TDSEComputationScheme : public BaseComputationScheme {
 public:

  int Initialize ();
  int InitWaveFunc (InitWave* initWave);
  int Run ();

};

}

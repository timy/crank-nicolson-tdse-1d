#include "BaseComputationScheme.hpp"
#include "Constants.hpp"
#include "Grid.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"

namespace CNTDSE1D {

class TDSEComputationScheme : public BaseComputationScheme {
 public:

  int Initialize ();
  int Run ();

};

}

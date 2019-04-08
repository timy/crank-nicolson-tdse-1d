#pragma once

namespace CNTDSE1D {

class IComputationScheme {
 public:
  virtual int Initialize () = 0;
  virtual int Run () = 0;
  virtual void Finalize () = 0;
};

}

#include <cstdio>
#include "IComputationScheme.hpp"

using namespace CNTDSE1D;
namespace CNTDSE1D {
extern IComputationScheme* g_pScheme;
}

int main (int argc, char* argv[]) {
  int ret;
  if ((ret = g_pScheme->Initialize ()) != 0) {
    printf ("App initialize failed, will exit now\n");
    return ret;
  }
  g_pScheme->Run ();
  g_pScheme->Finalize ();
  return 0;
}

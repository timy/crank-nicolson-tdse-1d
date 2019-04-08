#include <cstdio>
#include "IComputationScheme.hpp"

using namespace CNTDSE1D;
namespace CNTDSE1D {
extern IComputationScheme* g_pScheme;
}

#include <ctime>
int main (int argc, char* argv[]) {
  int ret;

  clock_t t = clock ();
  if ((ret = g_pScheme->Initialize ()) != 0) {
    printf ("App initialize failed, will exit now\n");
    return ret;
  }
  g_pScheme->Run ();
  g_pScheme->Finalize ();

  t = clock () - t;
  printf ("%lf s\n", ((float)t)/CLOCKS_PER_SEC);
  return 0;
}

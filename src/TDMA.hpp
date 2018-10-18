#pragma once
#include <complex>
#define complex std::complex<double>

// tri-diagonal matrix algorithm (Llewellyn Thomas's method)
class TDMA {
 public:
  int n;
  complex *cs, *ds, *x;

  TDMA (int n_): n(n_) {
    cs = new complex [n-1];
    ds = new complex [n];
    x = new complex [n];
  }
  ~TDMA () {
    delete[] cs;
    delete[] ds;
    delete[] x;
  }
  void solve (complex* a, complex* b, complex* c, complex* d) {
    cs[0] = c[0] / b[0];
    ds[0] = d[0] / b[0];
    for (int i = 1; i < n-1; i ++) {
      cs[i] = c[i] / (b[i] - cs[i-1] * a[i-1]);
      ds[i] = (d[i] - ds[i-1] * a[i-1]) / (b[i] - cs[i-1] * a[i-1]);
    }
    ds[n-1] = (d[n-1] - ds[n-2] * a[n-2]) / (b[n-1] - cs[n-2] * a[n-2]);
    x[n-1] = ds[n-1];
    for (int i = n-2; i >= 0; i --)
      x[i] = ds[i] - cs[i] * x[i+1];
  }
};

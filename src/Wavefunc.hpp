#pragma once
#include <cstdio>
#include <complex>
#include "TDMA.hpp"
#include "Grid.hpp"
#include "Potential.hpp"
#include "InitWave.hpp"
#include "Constants.hpp"

class Wavefunc {
 public:
  int nx;
  double dx;
  complex dt;
  complex s;
  double *x;
  complex *r0, *r1;
  complex *a, *b, *c, *d, *V, *psi;
  TDMA* tdma;
  Grid& g;
  Potential& pot;

  Wavefunc (Grid& g_, Potential& pot_, complex dt_) :
  g (g_), pot (pot_) {
    dt = dt_;
    nx = g.nx;
    dx = g.dx;
    x = new double [nx];
    r0 = new complex [nx]; // r_{j}
    r1 = new complex [nx]; // r_{j+1}
    a = new complex [nx-1];
    b = new complex [nx];
    c = new complex [nx-1];
    d = new complex [nx];
    psi = new complex [nx];
    V = new complex [nx];
    tdma = new TDMA(nx);

    s = dt / (4.*dx*dx);
    for (int i = 0; i < nx-1; i ++) {
      a[i] = -s;
      c[i] = -s; //conj (-s);
    }
  }
  ~Wavefunc () {
    delete[] x;
    delete[] r0;
    delete[] r1;
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] d;
    delete[] psi;
    delete[] V;
    delete tdma;
  }

  void init (InitWave* initWave) {
    for (int ix = 0; ix < nx; ix ++)
      psi[ix] = (*initWave) (ix);
  }

  void propagate (long it) {
    for (int ix = 0; ix < nx; ix ++) {
      V[ix] = pot.V (ix, it);
      r0[ix] = 0.5 * dt * (1./(dx*dx) + V[ix]);
      r1[ix] = 0.5 * dt * (1./(dx*dx) + V[ix]);
    }

    // construct a, b, c, d for the tri-diagonal linear system
    b[0] = r1[0] - I;
    d[0] = s * psi[1] - (I + r0[0]) * psi[0];
    for (int ix = 1; ix < nx-1; ix ++) {
      b[ix] = r1[ix] - I;
      d[ix] = s * (psi[ix+1] + psi[ix-1]) - (I + r0[ix]) * psi[ix];
    }
    b[nx-1] = r1[nx-1] - I;
    d[nx-1] = s * psi[nx-2] - (I + r0[nx-1]) * psi[nx-1];

    tdma->solve (a, b, c, d);

    for (int i = 0; i < nx; i ++)
      psi[i] = tdma->x[i];
  }

  void dump_norm_to_file (FILE* file) {
    for (int ix = 0; ix < nx; ix ++)
      fprintf (file, "%le ", real (conj (psi[ix]) * psi[ix]));
    fprintf (file, "\n");
  }

  void dump_wf_to_file (FILE* file) {
    for (int ix = 0; ix < nx; ix ++)
      fprintf (file, "%le %le ", real (psi[ix]), imag (psi[ix]));
    fprintf (file, "\n");
  }

  double norm () {
    double s = 0.5 * dx * (real (conj (psi[0]) * psi[0]) +
                           real (conj (psi[nx-1]) * psi[nx-1]));
    for (int ix = 1; ix < nx-1; ix ++)
      s += dx * real (conj (psi[ix]) * psi[ix]);
    return s;
  }

  void normalize () {
    double s = sqrt (norm ());
    for (int ix = 0; ix < nx; ix ++)
      psi[ix] /= s;
  }

  double energy () {
    double dx2 = 2*dx*dx;
    complex e = 0.5 * dx * (-conj (psi[1]-2.*psi[0]) / dx2 + V[0] * conj (psi[0])) * psi[0];
    for (int ix = 1; ix < nx-1; ix ++)
      e += dx * (-conj (psi[ix+1]-2.*psi[ix]+psi[ix-1]) / dx2 + V[ix] * conj (psi[ix])) * psi[ix];
    e += 0.5 * dx * (-conj (-2.*psi[nx-1]+psi[nx-2])/dx2 + V[nx-1] * conj (psi[nx-1])) * psi[nx-1];
    return real (e);
  }

  double expect_x () {
    double s = 0.;
    s += 0.5 * dx * g.x[0] * real (conj (psi[0]) * psi[0]);
    for (int ix = 1; ix < nx-1; ix ++)
      s += dx * g.x[ix] * real (conj (psi[ix]) * psi[ix]);
    s += 0.5 * dx * g.x[nx-1] * real (conj (psi[nx-1]) * psi[nx-1]);
    return s;
  }

  double expect_p () {
    complex s = 0.;
    s += 0.5 * conj (psi[0]) * psi[1];
    for (int ix = 1; ix < nx-1; ix ++)
      s += 0.5 * conj (psi[ix]) * (psi[ix+1]-psi[ix-1]);
    s += 0.5 * conj (psi[nx-1]) * (-psi[nx-2]);
    s *= - I;
    return real (s);
  }

  inline complex projection (complex* v) {
    complex c = 0.;
    for (int ix = 0; ix < nx; ix ++)
      c += conj (psi[ix]) * v[ix];
    c *= g.dx;
    return c;
  }

  inline void orthogonalize (complex* v) {
    complex c = this->projection (v);
    for (int ix = 0; ix < nx; ix ++)
      psi[ix] -= c * v[ix];
  }
};

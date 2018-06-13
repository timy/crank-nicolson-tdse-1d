#include <cstdio>
#include <complex>
#include <cstdlib>
#define complex std::complex<double>
const complex I = complex(0., 1.);

// tri-diagonal matrix algorithm (Llewellyn Thomas's method)
struct TDMA {
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

struct Grid {
  int nx;
  double dx, x0;
  double* x;
  Grid (int nx_, double dx_, double x0_): nx(nx_), dx(dx_), x0(x0_) {
    x = new double [nx];
    for (int ix = 0; ix < nx; ix ++)
      x[ix] = x0 + ix * dx;
  }
  ~Grid() {
    delete[] x;
  }
  void dump_to_file (FILE* file) {
    for (int ix = 0; ix < nx; ix ++)
      fprintf(file, "%lf\n", x[ix]);
  }
};

struct Potential {
  Grid& g;
  Potential(Grid& g_): g(g_) {}
  ~Potential() {}
  inline complex operator () (int ix, complex t) {
    double x = g.x[ix];

    return 0.5 * x * x;
    // return 0.01 * x * x + sin(0.2 * t) * x;
  }
  void dump_to_file(FILE* file, complex t) {
    for (int ix = 0; ix < g.nx; ix ++)
      fprintf(file, "%le ", real((*this)(ix, t)));
    fprintf(file, "\n");
  }
};

struct Wave {
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

  Wave(Grid& g_, Potential& pot_, complex dt_) :
    pot(pot_), g(g_), nx(g_.nx), dx(g_.dx), dt(dt_) {
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
      c[i] = -s; //conj(-s);
    }
  }
  ~Wave() {
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

  void propagate (complex t) {
    for (int ix = 0; ix < nx; ix ++) {
      V[ix] = pot(ix, t);
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

    tdma->solve(a, b, c, d);

    for (int i = 0; i < nx; i ++)
      psi[i] = tdma->x[i];
  }

  void dump_to_file (FILE* file) {
    for (int ix = 0; ix < nx; ix ++)
      fprintf(file, "%le ", real(conj(psi[ix])*psi[ix]));
    fprintf(file, "\n");
  }

  double norm () {
    double s = 0.5 * dx * (real(conj(psi[0]) * psi[0]) + real(conj(psi[nx-1]) * psi[nx-1]));
    for (int ix = 1; ix < nx-1; ix ++)
      s += dx * real(conj(psi[ix]) * psi[ix]);
    return s;
  }

  void normalize () {
    double s = sqrt(norm());
    for (int ix = 0; ix < nx; ix ++)
      psi[ix] /= s;
  }

  double energy () {
    double dx2 = 2*dx*dx;
    complex e = 0.5 * dx * (-conj(psi[1]-2.*psi[0])/dx2 + V[0]*conj(psi[0])) * psi[0];
    for (int ix = 1; ix < nx-1; ix ++)
      e += dx * (-conj(psi[ix+1]-2.*psi[ix]+psi[ix-1])/dx2 + V[ix]*conj(psi[ix])) * psi[ix];
    e += 0.5 * dx * (-conj(-2.*psi[nx-1]+psi[nx-2])/dx2 + V[nx-1]*conj(psi[nx-1])) * psi[nx-1];
    return real(e);
  }

  inline complex projection (complex* v) {
    complex c = 0.;
    for (int ix = 0; ix < nx; ix ++)
      c += conj(psi[ix]) * v[ix];
    c *= g.dx;
    return c;
  }

  inline void orthogonalize (complex* v) {
    complex c = this->projection(v);
    for (int ix = 0; ix < nx; ix ++)
      psi[ix] -= c * v[ix];
  }
};

struct Files {
  FILE* grid;
  FILE* time;
  FILE* norm;
  FILE* pot;
  Files () {
    grid = fopen("res/grid.dat", "w");
    time = fopen("res/time.dat", "w");
    norm = fopen("res/norm.dat", "w");
    pot  = fopen("res/pot.dat", "w");
  }
  ~Files () {
    fclose(grid);
    fclose(time);
    fclose(norm);
    fclose(pot);
  }
};

complex wf_gaussian (double x, double sigma) {
  return pow((1./(sigma*sigma))/M_PI, 0.25) * exp(-(x+20)*(x+20)/(2.*sigma*sigma)) * exp(I * 4. * x);
}

complex wf_random (double x) {
  return rand();
}

void solve_TISE (Grid& g, Potential& pot, Files& files) {

  // Calculate ground state by imaginary time propagation
  // Excited states are obtained by Gram-Schmidt orthogonalization

  const int nt = 2000;
  complex dt = -0.02 * I;
  Wave wf(g, pot, dt);

  int ns = 3;
  complex* psi_init = new complex [g.nx];
  for (int ix = 0; ix < g.nx; ix ++)
    psi_init[ix] = wf_random(g.x[ix]);

  complex** psi = new complex* [ns];
  for (int is = 0; is < ns; is ++)
    psi[is] = new complex [g.nx];

  // start propagation
  for (int is = 0; is < ns; is ++) {
    for (int ix = 0; ix < g.nx; ix ++)
      wf.psi[ix] = psi_init[ix];
    for (int it = 0; it < nt; it ++) {
      complex t = 1. * it * dt;
      for (int is1 = 0; is1 < is; is1 ++)
        wf.orthogonalize(psi[is1]);
      wf.propagate(t);
      wf.normalize(); // used for imaginary time propagation

      if (is == ns-1) {
        if (it % 20 == 0) {
          fprintf(files.time, "%lf\n", abs(t));
          wf.dump_to_file(files.norm);
          printf("step:%d\tnorm:%le energy:%le\n", it, wf.norm(), wf.energy());
        }
      }
    }
    for (int ix = 0; ix < g.nx; ix ++)
      psi[is][ix] = wf.psi[ix];

    printf("Energy of state %d: %le\n", is, wf.energy());
    // output...
  }
  for (int is = 0; is < ns; is ++)
    delete[] psi[is];
  delete[] psi_init;
}

void solve_TDSE (Grid& g, Potential& pot, Files& files) {
  const int nt = 4000;
  double dt = 0.02;
  Wave wf(g, pot, dt);
  for (int i = 0; i < g.nx; i ++)
    wf.psi[i] = wf_gaussian(g.x[i], 2.);

  wf.dump_to_file(files.norm);
  for (int it = 0; it < nt; it ++) {
    double t = it * dt;
    fprintf(files.time, "%lf\n", t);
    wf.propagate(t);
    wf.dump_to_file(files.norm);
    pot.dump_to_file(files.pot, t);

    if (it % 20 == 0)
      printf("step:%d\tnorm:%le energy:%le\n", it, wf.norm(), wf.energy());
  }
}

int main(int argc, char* argv[]) {

  const int nx = 2001;
  double x0 = -40.;
  double dx = 0.04;

  Grid g(nx, dx, x0);
  Potential pot(g);
  Files files;

  g.dump_to_file(files.grid);
  pot.dump_to_file(files.pot, 0.);

  solve_TISE(g, pot, files);
  // solve_TDSE(g, pot, files);

  return 0;
}

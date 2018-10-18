#pragma once
#include "InitWave.hpp"

class InitWaveGaussian : public InitWave {
 public:
  double sigma;
  double k;
  double x0;
  inline complex operator () (long ix) {
    double x = g->x[ix];
    return pow ((1./(sigma*sigma))/M_PI, 0.25) *
      exp (-(x-x0)*(x-x0)/(2.*sigma*sigma)) * exp (I * k * x);
  }
};

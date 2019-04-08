#include "TISEComputationScheme.hpp"
#include "Wavefunc.hpp"
#include "Files.hpp"
#include <iostream>
#include <fstream>

int CNTDSE1D::TISEComputationScheme::Initialize () {
  BaseComputationScheme::Initialize ();
  std::cout << "START: TISEComputationScheme::Initialize" << std::endl;
  std::cout << "  END: TISEComputationScheme::Initialize" << std::endl;
  return 0;
}

int CNTDSE1D::TISEComputationScheme::Run () {
  std::cout << "START: TISEComputationScheme::Run" << std::endl;
  std::cout << "ERROR: A concrete TISE scheme should be specified!" << std::endl;
  std::cout << "  END: TISEComputationScheme::Run" << std::endl;
  return 0;
}

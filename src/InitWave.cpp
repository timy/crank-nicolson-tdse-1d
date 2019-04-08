#include "InitWave.hpp"
#include <iostream>

int InitWave::Initialize (Grid *grid) {
  std::cout << "START: InitWave::Initialize" << std::endl;
  g = grid;
  std::cout << "  END: InitWave::Initialize" << std::endl;
  return 0;
}

void InitWave::Finalize () {
  std::cout << "START: InitWave::Finalize" << std::endl;
  std::cout << "  END: InitWave::Finalize" << std::endl;
};

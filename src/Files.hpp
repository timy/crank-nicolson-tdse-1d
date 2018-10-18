#pragma once
#include <cstdio>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Files {
 public:
  FILE* grid;
  FILE* time;
  FILE* norm;
  FILE* pot;

  Files () {
    char dir[] = "res";
    if (!fs::is_directory (dir) || !fs::exists (dir)) {
      printf ("Directory \"%s\" does not exist, create new one.\n", dir);
      fs::create_directory (dir);
    }

    char filename[256];
    sprintf (filename, "%s/%s", dir, "grid.dat");
    grid = fopen (filename, "w");
    sprintf (filename, "%s/%s", dir, "time.dat");
    time = fopen (filename, "w");
    sprintf (filename, "%s/%s", dir, "norm.dat");
    norm = fopen (filename, "w");
    sprintf (filename, "%s/%s", dir, "pot.dat");
    pot  = fopen (filename, "w");
  }
  ~Files () {
    fclose (grid);
    fclose (time);
    fclose (norm);
    fclose (pot);
  }
};

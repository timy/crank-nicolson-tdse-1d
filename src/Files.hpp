#pragma once
#include <cstdio>
#include <cstring>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Files {
 public:
  char dir[128];
  int n_files;
  FILE** files;

  Files (int n_files=1) : n_files (n_files) {
    try {
      initialize ();
    } catch (const char* s) {
      return;
    }
    set_dir (".");
  }

  Files (const char* filename, const char* flag, const char* dir_, int n_files)
  : n_files (n_files) {
    try {
      initialize ();
    } catch (const char* s) {
      return;
    }
    set_dir (dir_);
    this->open (filename, flag);
  }

  ~Files () {
    if (n_files > 0) {
      if (files[0] != nullptr)
        this->close ();
      delete[] files;
    }
  }

  void initialize () {
    if (n_files < 1) {
      fprintf (stderr, "n_files = %d is invalid!\n", n_files);
      throw "invalid n_files";
    }
    files = new FILE*[n_files];
    for (int i = 0; i < n_files; i ++)
      files[i] = nullptr;
  }

  void open (const char* filename, const char* flag) {
    if (files[0] != nullptr) {
      fprintf (stderr, "Attempt to reopen file [%s] "
               "that is not yet closed!\n", filename);
      return;
    }

    ensure_dir_exist ();
    char tmp[256];
    for (int i = 0; i < n_files; i ++) {
      sprintf (tmp, "%s/%s_%d.dat", dir, filename, i);
      printf ("open file %s\n", tmp);
      files[i] = fopen (tmp, flag);
    }
  }

  void close () {
    if (files[0] == nullptr) {
      fprintf (stderr, "Attempt to close file that is not yet opened!\n");
      return;
    }
    for (int i = 0; i < n_files; i ++)
      fclose (files[i]);
  }

  void set_dir (const char* dirname) {
    strcpy (dir, dirname);
  }

  inline FILE* operator [] (int i) { return files[i]; }

  void ensure_dir_exist () {
    if (!fs::is_directory (dir) || !fs::exists (dir)) {
      printf ("Directory \"%s\" does not exist, create new one.\n", dir);
      fs::create_directory (dir);
    }
  }
};

//////////////////////////////
/// Demo and test routines ///
//////////////////////////////

// // used for ----- Demo 3 -----
// class Grid {
//  public:
//   Files files{"test", "w", "res", 3};
// };


// int main (int argc, char* argv[]) {
//   // // ----- Demo 1 -----
//   // Files files("test", "w", "res", 3);

//   // // ----- Demo 2 -----
//   // Files files(3);
//   // files.set_dir ("res1");
//   // files.open ("test", "w");

//   // for (int i = 0; i < 10; i ++) {
//   //   fprintf (files[0], "%d\n", i);
//   // }

//   // // "close" can also be neglected, except you wish to
//   // // reopen files for other actual physical files
//   // files.close();

//   // ----- Demo 3 -----
//   Grid g;
//   for (int i = 0; i < 10; i ++) {
//     fprintf (g.files[0], "%d\n", i);
//   }

//   return 0;
// }

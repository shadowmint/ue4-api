#include <npp/test/test_suite.h>
#include <npp/format.h>
#include <base64/encode.h>
#include <base64/decode.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tinydir.h"

using namespace npp;

// Headers.
void ProcessFolder(char *source, char *destination);
void ProcessFile(const char *source, char *filename, char *destination);
string GenerateClassName(const char *filename);

int main(int argc, char **argv) {
  if (argc == 3)
    ProcessFolder(argv[1], argv[2]);
  else
    printf("usage: %s [source] [target]\n", argv[0]);
  return 0;
}

/// Process all the folders in the target location and invoke process_file()
/// on each target.
void ProcessFolder(char *source, char *destination) {
  tinydir_dir dir;
  tinydir_open(&dir, source);
  while (dir.has_next) {
      tinydir_file file;
      tinydir_readfile(&dir, &file);
      if (!file.is_dir) {
        auto path = Format("%s/%s", source, file.name);
        ProcessFile(path.c_str(), file.name, destination);
      }
      tinydir_next(&dir);
  }
  tinydir_close(&dir);
}

/// Generate an inline class file for this binary asset
void ProcessFile(const char *source, char *filename, char *destination) {
  auto class_name = GenerateClassName(filename);
  auto file_name = Format("%s/%s.h", destination, class_name.c_str());
  printf("- GENERATE: %s -> %s\n", source, file_name.c_str());
  base64::encoder E;
  std::ofstream fp;
  std::ifstream fp_in;
  fp_in.open(source);
  if (fp_in.fail()) {
    printf("-   FAILED: Invalid input: %s\n", strerror(errno));
  }
  else {
    fp.open(file_name.c_str());
    if (fp.fail()) {
      printf("-   FAILED: Invalid output: %s\n", strerror(errno));
    }
    else {
      fp << "#pragma once\n";
      fp << "namespace assets {\n";
      fp << "  const char *" << class_name.c_str() << " = R\"(\n";
      E.encode(fp_in, fp);
      fp << "" << ")\";\n";
      fp << "}\n";
      fp.close();
    }
    fp_in.close();
  }
}

/// Generate a classname for this class
string GenerateClassName(const char *source) {
  auto rtn = Format("ASSET__%s", source);
  std::replace(rtn.begin(), rtn.end(), ' ', '_');
  std::replace(rtn.begin(), rtn.end(), '.', '_');
  return rtn;
}

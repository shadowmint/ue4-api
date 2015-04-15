#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

namespace npp {

  /// Use printf style formatting to format a string value
  template<typename ... Args> string Format(const string& format, Args ... args) {
    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);
    unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return string(buf.get(), buf.get() + size);
  }
}

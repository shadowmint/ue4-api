#include <npp/test/test_suite.h>
#include <npp/format.h>
#include <base64/encode.h>
#include <base64/decode.h>
#include <string>
#include <iostream>
#include <sstream>
#include "data/ASSET__CMakeLists_txt.h"
#include "data/ASSET__README_md.h"

using namespace npp;
using namespace npp::test;

void test_decode_inline_1() {
  std::stringstream sin;
  std::stringstream sout;
  base64::decoder E;

  sin << assets::ASSET__CMakeLists_txt;
  E.decode(sin, sout);
  auto output = sout.str();
  ASSERT(output.length() > 0);
}

void test_decode_inline_2() {
  std::stringstream sin;
  std::stringstream sout;
  base64::decoder E;

  sin << assets::ASSET__README_md;
  E.decode(sin, sout);
  auto output = sout.str();
  ASSERT(output.length() > 0);
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_decode_inline_1)
      TEST(test_decode_inline_2)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

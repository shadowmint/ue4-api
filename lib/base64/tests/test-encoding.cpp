#include <npp/test/test_suite.h>
#include <npp/format.h>
#include <base64/encode.h>
#include <base64/decode.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace npp;
using namespace npp::test;

void test_encode_decode() {
  std::stringstream sin;
  std::stringstream sout;
  std::stringstream sout2;

  sin << "Hello World";
  base64::encoder E;
  E.encode(sin, sout);
  auto output = sout.str();

  base64::decoder DE;
  DE.decode(sout, sout2);
  auto value2 = sout2.str();

  ASSERT(sin.str() == value2);
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_encode_decode)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

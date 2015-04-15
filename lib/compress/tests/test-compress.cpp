#include <npp/test/test_suite.h>
#include <npp/format.h>
#include <compress/compress.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace npp;
using namespace npp::test;

void test_compress_decompress() {
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_compress_decompress)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

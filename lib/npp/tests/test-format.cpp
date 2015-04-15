#include <npp/test/test_suite.h>
#include <npp/format.h>

using namespace npp;
using namespace npp::test;

void test_format_string() {
  auto value = Format("%d %s", 100, "Hello World");
  ASSERT(strcmp(&value[0], "100 Hello World") == 0);
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_format_string)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

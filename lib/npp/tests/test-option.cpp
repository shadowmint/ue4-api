#include <npp/test/test_suite.h>
#include <npp/option.h>

using namespace npp;
using namespace npp::test;

Option<int> test_fixture(int value) {
  if (value >= 0) {
    return Some<int>(value + 10);
  }
  return None<int>();
}

void test_some_helper() {
  auto value = Some<int>(100);
  ASSERT(value);
  ASSERT(*value == 100);
}

void test_none_helper() {
  auto value = None<int>();
  ASSERT(!value);
}

void test_then_fixture() {
  auto value = test_fixture(100);
  ASSERT(value && *value == 110);
  value = test_fixture(-10);
  ASSERT(!value);
}

void test_then() {
  bool found = false;
  test_fixture(100).Then([&] (int v) { found = true; ASSERT(v == 110); });
  test_fixture(-10).Then([] (int v) { UNREACHABLE; });
  if (!test_fixture(10).Then([] (int v) {})) {
    UNREACHABLE;
  }
  ASSERT(found);
}

void test_or() {
  auto value = test_fixture(100).Or(-1);
  ASSERT(value == 110);

  value = test_fixture(-100).Or(-1);
  ASSERT(value == -1);
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_some_helper)
      TEST(test_none_helper)
      TEST(test_then_fixture)
      TEST(test_then)
      TEST(test_or)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

#include <npp/test/test_suite.h>
#include <npp/iterator.h>
#include <npp/types.h>

using namespace std;
using namespace npp;
using namespace npp::test;

vector<i32> test_fixture() {
  vector<i32> vec;
  for (int i = 0; i < 25; ++i) {
    vec.push_back(100+i);
  }
  return vec;
}

Iterator<vector<i32>*, i32> test_iterator_factory(vector<i32> *vec) {
  return iter<vector<i32>, i32>(vec, [] (vector<i32> *vec, std::function< bool(i32 value) > handler) {
    for (auto v = vec->begin(); v != vec->end(); ++v) {
      if (!handler(*v)) {
        break;
      }
    }
  });
}

Iterator<vector<i32>*, i32> fail_iterator_factory(vector<i32> *vec) {
  return iter<vector<i32>, i32>(0, [] (vector<i32> *vec, std::function< bool(i32 value) > handler) {
    for (auto v = vec->begin(); v != vec->end(); ++v) {
      if (!handler(*v)) {
        break;
      }
    }
  });
}

Iterator<vector<i32>*, i32> empty_iterator_factory(vector<i32> *vec) {
  return iter<vector<i32>, i32>(vec, [] (vector<i32> *vec, std::function< bool(i32 value) > handler) {});
}

void test_simple_iterator() {
  auto vec = test_fixture();
  auto item = test_iterator_factory(&vec);
  int count = 0;
  item.Each([&] (i32 value) { ++count; });
  ASSERT(count == 25);
}

void test_fail_iterator() {
  auto vec = test_fixture();
  try {
    auto item = fail_iterator_factory(&vec);
    UNREACHABLE;
  }
  catch(std::exception e) {
  }
}

void test_first() {
  auto vec = test_fixture();
  auto item = test_iterator_factory(&vec);
  auto value = item.First();
  ASSERT(value);
  ASSERT(*value == 100);
}

void test_count() {
  auto vec = test_fixture();
  auto item = test_iterator_factory(&vec);
  auto value = item.Count();
  ASSERT(value == 25);
}

void test_any() {
  auto vec = test_fixture();
  auto valid = test_iterator_factory(&vec);
  auto not_valid = empty_iterator_factory(&vec);
  ASSERT(valid.Any());
  ASSERT(!not_valid.Any());
}

void test_collect() {
  auto vec = test_fixture();
  auto valid = test_iterator_factory(&vec);
  auto all = valid.Collect();
  ASSERT(all.size() == 25);
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_simple_iterator)
      TEST(test_fail_iterator)
      TEST(test_first)
      TEST(test_count)
      TEST(test_any)
      TEST(test_collect)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

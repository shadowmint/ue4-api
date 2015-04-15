#include <npp/test/test_suite.h>
#include <npp/types.h>
#include <npp/resource.h>

using namespace npp;
using namespace npp::test;

int alloc_counter = 0;
int dealloc_counter = 0;

enum RType {
  ThingOne = 1,
  ThingTwo = 2
};

class RValue : public Resource<RType, i32> {
  public:
    RValue(int value) : Resource(ThingOne, value) {
      alloc_counter += 1;
    }
    ~RValue() {
      dealloc_counter += 1;
    }
    Resource<RType, i32>* Clone() {
      return new RValue(this->value);
    }
};

class LValue : public Resource<RType, i32> {
  public:
    LValue(int value) : Resource(ThingTwo, value) {
      alloc_counter += 1;
    }
    ~LValue() {
      dealloc_counter += 1;
    }
    Resource<RType, i32>* Clone() {
      return new LValue(this->value);
    }
};

void test_alloc_dealloc() {
  auto foo = new RValue(100);
  delete foo;
  ASSERT(alloc_counter == dealloc_counter);
}

void test_push() {
  auto counter = alloc_counter;
  auto foo = new RValue(100);
  foo->Push(new RValue(200));
  delete foo;
  ASSERT(alloc_counter == counter + 2);
  ASSERT(alloc_counter == dealloc_counter);
}

void test_iter() {
  auto count = 0;
  auto acount = alloc_counter;
  auto foo = new RValue(100);
  foo->Push(new RValue(101));
  foo->Push(new LValue(200));
  foo->Push(new LValue(201));
  foo->Push(new LValue(202));
  foo->Iter<Resource<RType, i32>>().Each([&] (Resource<RType, i32> *v) {
    count += 1;
  });
  delete foo;
  ASSERT(count == 5);
  ASSERT(alloc_counter == (acount + 5));
  ASSERT(dealloc_counter == (acount + 5));
}

void test_iter_id() {
  auto l_count = 0;
  auto r_count = 0;
  auto foo = new RValue(100);
  foo->Push(new RValue(101));
  foo->Push(new LValue(200));
  foo->Push(new LValue(201));
  foo->Push(new LValue(202));
  foo->Iter<LValue>(ThingTwo).Each([&] (LValue *l) {
    l_count += 1;
  });
  foo->Iter<RValue>(ThingOne).Each([&] (RValue *l) {
    r_count += 1;
  });
  delete foo;
  ASSERT(l_count == 3);
  ASSERT(r_count == 2);
}

void test_filter_by_function() {
  auto foo = new RValue(100);
  foo->Push(new RValue(101));
  foo->Push(new LValue(100));
  foo->Push(new LValue(201));
  foo->Push(new LValue(202));
  auto filtered = foo->Filter([] (Resource<RType, i32>* value) {
    return **value == 100;
  }).Or(NULL);
  delete foo;
  ASSERT(filtered);
  ASSERT(filtered->Count() == 2);
  delete filtered;
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_alloc_dealloc)
      TEST(test_push)
      TEST(test_iter)
      TEST(test_iter_id)
      TEST(test_filter_by_function);
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

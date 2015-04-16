#include <npp/test/test_suite.h>
#include <npp/format.h>
#include <compress/compress.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace npp;
using namespace npp::test;

void test_block() {
  auto b = compress::Block("Hello World");
  ASSERT(b.length == 11);
  ASSERT(b.data != NULL);

  auto value = b.AsStr().Or("");
  ASSERT(value == "Hello World");
}

void test_block_pointer() {
  auto b = new compress::Block("Hello World");
  ASSERT(b->length == 11);
  ASSERT(b->data != NULL);

  auto value = b->AsStr().Or("");
  ASSERT(value == "Hello World");

  delete b;
}

void test_deflate() {
  auto b = compress::Block("Helloooooooooooooooooooooooooo World Helloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo World");
  auto d = b.Deflate().Or(NULL);
  ASSERT(d);
  ASSERT(d->length < b.length);
  delete d;
}

void test_simple_inflate() {
  auto b = compress::Block("Helloooooooooooooooooooooooooo World Helloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo World");

  auto d = b.Deflate().Or(NULL);
  ASSERT(d);

  auto i = d->Inflate(1024).Or(NULL);
  ASSERT(i);
  ASSERT(i->length == b.length);
  ASSERT(i->AsStr() == b.AsStr());

  delete d;
  delete i;
}

void test_short_inflate() {
  auto b = compress::Block("Helloooooooooooooooooooooooooo World Helloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo World");

  auto d = b.Deflate().Or(NULL);
  ASSERT(d);

  auto i = d->Inflate(613).Or(NULL);
  ASSERT(i);
  ASSERT(i->length == b.length);
  ASSERT(i->AsStr() == b.AsStr());

  auto j = d->Inflate(612).Or(NULL);
  ASSERT(!j);

  delete d;
  delete i;
  delete j;
}

void test_dynamic_inflate() {
  auto b = compress::Block("Helloooooooooooooooooooooooooo World Helloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo WorldHelloooooooooooooooooooooooooo World");

  auto d = b.Deflate().Or(NULL);
  ASSERT(d);

  auto j = d->Inflate().Or(NULL);
  ASSERT(j);
  ASSERT(j->length == b.length);
  ASSERT(j->AsStr() == b.AsStr());

  delete d;
  delete j;
}

class Tests: public TestSuite {
  public:
    Tests() {
      TEST(test_block)
      TEST(test_block_pointer)
      TEST(test_deflate)
      TEST(test_simple_inflate)
      TEST(test_short_inflate)
      TEST(test_dynamic_inflate)
    }
};

int main(int argc, char **argv) {
  return (new Tests())->Report();
}

#include "test_library.hpp"
#include <string>
#include <stdio.h>

struct TestTestCase: public TestCase {
  virtual void test() {
    checkTrue(true);
    checkEqual(1, 1);
    checkEqual(3.0, 3.0);
    checkEqual(std::string("foo"), std::string("foo"));
  }
};
REGISTER_TEST(TestTestCase)


int main() {
  printf("Running tests...\n");
  TestSuite::getInstance().runTests();
  printf("%d test(s) run.\n\n", TestSuite::getInstance().getNumTests());
}

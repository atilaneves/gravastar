#include "test_library.hpp"
#include <memory>
#include <assert.h>


void TestCase::doTest() {
  setup();
  test();
  shutdown();
}


TestSuite& TestSuite::getInstance() {
  static TestSuite instance;
  return instance;
}

bool TestSuite::registerTest(TestCaseCreator creator) {
  _creators.push_back(creator);
  return true;
}

void TestSuite::runTests() {
  for(auto creator: _creators) {
    std::unique_ptr<TestCase> testCase {creator()};
    testCase->doTest();
  }
}

void checkTrue(bool condition) {
  assert(condition);
}

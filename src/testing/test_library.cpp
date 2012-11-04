#include "test_library.hpp"
#include <memory>
#include <iostream>

bool TestCase::doTest() {
  setup();
  test();
  shutdown();
  return !_failed;
}

bool TestCase::verifyTrue(bool condition) {
  _failed = !condition;
  return condition;
}


TestSuite& TestSuite::getInstance() {
  static TestSuite instance;
  return instance;
}

bool TestSuite::registerTest(const std::string& name, const TestCaseCreator& creator) {
  return _creators.insert(std::make_pair(name, creator)).second;
}

void TestSuite::addFailure(const std::string& name) {
  _failures.push_back(name);
}

void TestSuite::runTests() {
  for(const auto& it: _creators) {
    std::unique_ptr<TestCase> testCase { it.second() };
    if(!testCase->doTest()) addFailure(it.first);
  }

  for(auto failure: _failures)
    std::cout << "Test " << failure << " failed." << std::endl;
}

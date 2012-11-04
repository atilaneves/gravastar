#ifndef TEST_LIBRARY_HPP
#define TEST_LIBRARY_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <functional>

class TestCase {
public:

  TestCase():_failed(false) { }
  virtual ~TestCase() { }
  bool doTest();

protected:

  template<typename T, typename U>
  bool verifyEqual(T t, U u) {
    if(t != u) _failed = true;
    return !_failed;
  }

  bool verifyTrue(bool condition);
  virtual void test() = 0;
  virtual void setup()    { }
  virtual void shutdown() { }

private:

  bool _failed;

};

typedef std::function<TestCase*()> TestCaseCreator;

class TestSuite {
public:

  static TestSuite& getInstance();
  bool registerTest(const std::string& name, const TestCaseCreator& creator);
  void addFailure(const std::string& name);
  void runTests();
  int getNumTests()    const { return _creators.size(); }
  int getNumFailures() const { return _failures.size(); }

private:

  std::map<std::string, TestCaseCreator> _creators;
  std::vector<std::string> _failures;

  TestSuite() { }
  TestSuite(const TestSuite&);
  TestSuite& operator=(const TestSuite&);

};


#define REGISTER_TEST(test) \
namespace { \
    TestCase* create_##test() { \
        return new test; \
    } \
    bool result_##test = TestSuite::getInstance().registerTest(#test, create_##test); \
}


#define checkEqual(value, expected) \
  { \
     bool check = verifyEqual(value, expected); \
     if(!check) \
       std::cout << __FILE__ << ":" << __LINE__ << \
	 " Value " #value " is not the expected " << expected << std::endl; \
  }

#define checkTrue(value) \
  { \
     bool check = verifyTrue(value); \
     if(!check) \
       std::cout << __FILE__ << ":" << __LINE__ << \
	 " Value " #value " is not true" << std::endl; \
  }



#endif

#ifndef TEST_LIBRARY_HPP
#define TEST_LIBRARY_HPP

#include <vector>
#include <assert.h>

class TestCase {
public:

  virtual ~TestCase() { }
  void doTest();

protected:

  virtual void test() = 0;
  virtual void setup()    { }
  virtual void shutdown() { }

};

typedef TestCase* (*TestCaseCreator)();

class TestSuite {
public:

  static TestSuite& getInstance();
  bool registerTest(TestCaseCreator creator);
  void runTests();
  int getNumTests() const { return _creators.size(); }

private:

  std::vector<TestCaseCreator> _creators;

  TestSuite() { }
  TestSuite(const TestSuite&);
  TestSuite& operator=(const TestSuite&);

};


void checkTrue(bool condition);

template<typename T, typename U>
inline void checkEqual(T t, U u) {
  assert(t == u);
}

#define REGISTER_TEST(test) \
namespace { \
    TestCase* create_##test() { \
        return new test; \
    } \
    bool result_##test = TestSuite::getInstance().registerTest(create_##test); \
}

#endif

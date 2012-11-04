#include "test_library.hpp"
#include <string>
#include <iostream>

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
    std::cout << "Running tests..." << std::endl;
    TestSuite::getInstance().runTests();
    std::cout << TestSuite::getInstance().getNumTests() << " test(s) run, " <<
        TestSuite::getInstance().getNumFailures() << " failed.\n\n";
}

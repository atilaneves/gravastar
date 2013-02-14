#include "test_library.hpp"
#include <string>
#include <iostream>

struct FirstTestCase: public TestCase {
    virtual void test() {
        checkTrue(true);
        checkEqual(1, 1);
        checkEqual(3.0, 3.0);
        checkEqual(std::string("foo"), std::string("foo"));
    }
};
REGISTER_TEST(FirstTestCase)

struct AnotherTestCase: public TestCase {
    virtual void test() {
        checkEqual(std::string("bar"), std::string("bar"));
        checkEqual("baz", "baz");
    }
};
REGISTER_TEST(AnotherTestCase)

struct YetAnotherTestCase: public TestCase {
    virtual void test() {
        checkEqual(1, 1);
    }
};
REGISTER_TEST(YetAnotherTestCase)




int main() {
    std::cout << "Running tests..." << std::endl;
    TestSuite::getInstance().runTests();
    std::cout << TestSuite::getInstance().getNumTests() << " test(s) run, " <<
                 TestSuite::getInstance().getNumFailures() << " failed.\n\n";

    if(!TestSuite::getInstance().getNumFailures()) {
        std::cout << "\nOK!\n\n";
        return 0;
    }

    return 1; //oops
}

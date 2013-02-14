#include "TestCase.hpp"

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

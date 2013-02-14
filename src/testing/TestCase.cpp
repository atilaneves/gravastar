#include "TestCase.hpp"

TestCase::TestCase():
    _failed(false) {
}

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


bool TestCase::fail() {
    _failed = true;
    return false;
}

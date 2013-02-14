#include "test_library.hpp"
#include <memory>
#include <iostream>
#include <boost/format.hpp>

static const int DECIMALS = 3;

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
    static size_t index = 0; //just to order the tests as they're created
    //prepend registration order to unit test name
    const std::string format = "%0" + std::to_string(DECIMALS) +"d";
    const auto realName = (boost::format(format) % index++).str() + name;
    return _creators.insert(std::make_pair(realName, creator)).second;
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
        //substr removes leading index from name
        std::cout << "Test " << failure.substr(DECIMALS) << " failed." << std::endl;
}

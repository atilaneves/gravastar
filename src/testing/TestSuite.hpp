#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include <map>
#include <vector>
#include <string>
#include <chrono>

#include "TestCase.hpp"

class TestSuite {
public:


    TestSuite();
    /**
     * Returns the elapsed time in seconds
     */
    double run();
    double run(const std::vector<std::string>& testsToRun);

    int getNumTestsRun() const { return _numTestsRun; }
    int getNumFailures() const { return _failures.size(); }

private:

    std::vector<std::string> _failures;
    size_t _numTestsRun;

    void addFailure(const std::string& name);
};


#endif

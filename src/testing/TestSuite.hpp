#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include <map>
#include <vector>
#include <string>
#include <chrono>

#include "TestCase.hpp"

class TestSuite {
public:

    static TestSuite& getInstance();
    bool registerTest(const std::string& name, const std::string& path, const TestCaseCreator& creator);
    void addFailure(const std::string& name);
    /**
     * Returns the elapsed time in seconds
     */
    double runTests(const std::vector<std::string>& testsToRun = std::vector<std::string>());
    int getNumTestsRun() const { return _numTestsRun; }
    int getNumFailures() const { return _failures.size(); }
    const std::vector<std::string> getPaths() const;

private:

    std::map<std::string, TestCaseCreator> _nameToCreators;
    std::map<std::string, std::string> _pathToNames;
    std::vector<std::string> _failures;
    size_t _numTestsRun;

    TestSuite():_numTestsRun() { }
    TestSuite(const TestSuite&);
    TestSuite& operator=(const TestSuite&);
};


#endif

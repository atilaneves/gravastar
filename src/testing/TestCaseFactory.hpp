#ifndef TESTCASEFACTORY_HPP_
#define TESTCASEFACTORY_HPP_

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "TestCase.hpp"

class TestCaseFactory {
public:

    using TestCases = std::vector<std::unique_ptr<TestCase>>;

    static TestCaseFactory& getInstance();
    bool registerTest(const std::string& path, const TestCaseCreator& creator);
    const std::vector<std::string> getPaths() const;
    TestCases createTests(const std::string& testPathToRun) const;

private:

    std::map<std::string, TestCaseCreator> _pathToCreators;

    TestCaseFactory() { }
    TestCaseFactory(const TestCaseFactory&);
    TestCaseFactory& operator=(const TestCaseFactory&);
};



#endif

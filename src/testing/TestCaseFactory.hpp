#ifndef TESTCASEFACTORY_HPP_
#define TESTCASEFACTORY_HPP_

#include <map>
#include <vector>
#include <string>
#include <memory>
#include "TestCase.hpp"

class TestCaseFactory {
public:

    struct TestCaseWithPath;
    using TestCases = std::vector<TestCaseWithPath>;

    static TestCaseFactory& getInstance();
    bool registerTest(const std::string& path, const TestCaseCreator& creator);
    const std::vector<std::string> getPaths() const;
    TestCases createTests(const std::string& testPathToRun) const;

    struct TestCaseWithPath {
        const std::string _path;
        std::unique_ptr<TestCase> _testCase;
        TestCaseWithPath(const std::string& p, TestCase* t):_path(p), _testCase(t) { }
        TestCaseWithPath(TestCaseWithPath&& other):
            _path(std::move(other._path)), _testCase(std::move(other._testCase)) {}
        const std::string& getPath() const { return _path; }
        bool doTest() { return _testCase->doTest(); }
    };

private:

    std::map<std::string, TestCaseCreator> _pathToCreators;

    TestCase* createTest(const std::string& path) const;

    TestCaseFactory() { }
    TestCaseFactory(const TestCaseFactory&);
    TestCaseFactory& operator=(const TestCaseFactory&);
};

template<class T> TestCase* testCaseCreator() { return new T; }



#endif

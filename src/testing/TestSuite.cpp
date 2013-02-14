#include "TestSuite.hpp"
#include <memory>
#include <iostream>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>


TestSuite& TestSuite::getInstance() {
    static TestSuite instance;
    return instance;
}


bool TestSuite::registerTest(const std::string& name, const std::string& path, const TestCaseCreator& creator) {
    const bool insertion = _nameToCreators.insert(std::make_pair(name, creator)).second;
    if(insertion) {
        return _pathToNames.insert(std::make_pair(path, name)).second;
    }
    return false;   
}


void TestSuite::addFailure(const std::string& name) {
    _failures.push_back(name);
}


static bool isToRun(const std::string& testPathToRun, const std::string& testPath) {
    /**
     * 'Folder' paths end with '/' and match everything in them, foo/bar/ gets foo/bar/baz and foo/bar/boo
     * 'Exact' paths end with anything else and only match exactly
     */
    if(boost::ends_with(testPathToRun, "/")) {
        return boost::starts_with(testPath, testPathToRun);
    } else {
        return testPath == testPathToRun;
    }
}


template<typename CLOCK, typename START>
static double getElapsedSeconds(CLOCK clock, START start) {
    return ((clock.now() - start)).count() / 1000.0;
}

double TestSuite::runTests(const std::vector<std::string>& testsToRun) {
    const std::vector<std::string> actualTestsToRun = testsToRun.empty() ? getPaths() : testsToRun;

    std::cout << "Running tests..." << std::endl;
    std::chrono::high_resolution_clock clock;
    const auto start = clock.now();

    for(const auto& testPathToRun: actualTestsToRun) {
        for(const auto& pathToName: _pathToNames) {

            const auto& testPath = pathToName.first;
            const auto& testName = pathToName.second;
            
            if(!isToRun(testPathToRun, testPath)) continue;

            if(_nameToCreators.find(testName) == _nameToCreators.end()) {
                std::cout << "Could not create test case " << testName <<
                    " for test path " << testPath << std::endl;
                return getElapsedSeconds(clock, start);
            }

            std::unique_ptr<TestCase> testCase { _nameToCreators[testName]() };
            if(!testCase->doTest()) addFailure(testPath);
            _numTestsRun++;
        }
    }
               
    for(auto failure: _failures) {
        std::cout << "Test " << failure << " failed." << std::endl;        
    }

    return getElapsedSeconds(clock, start);
}


const std::vector<std::string> TestSuite::getPaths() const {
    std::vector<std::string> paths;
    for(const auto& nameToPath: _pathToNames) {
        paths.emplace_back(nameToPath.first);
    }
    return paths;
}

#include "TestSuite.hpp"
#include "TestCaseFactory.hpp"
#include <memory>
#include <iostream>
#include <future>


TestSuite::TestSuite(std::launch policy):
    _policy(policy), _numTestsRun() { 
}


void TestSuite::addFailure(const std::string& name) {
    _failures.push_back(name);
}


template<typename CLOCK, typename START>
static double getElapsedSeconds(CLOCK clock, START start) {
    return ((clock.now() - start)).count() / 1000000.0;
}


double TestSuite::run() {
    const auto paths = TestCaseFactory::getInstance().getPaths();
    std::cout << "Running all " << paths.size() << " tests" << std::endl; 
    return run(paths);
}


double TestSuite::run(const std::vector<std::string>& pathsToRun) {
    std::cout << "Running tests...\n\n";
    std::chrono::high_resolution_clock clock;
    const auto start = clock.now();

    std::vector<std::future<void>> futures;
    for(const auto& pathToRun: pathsToRun) {
        auto testCases = TestCaseFactory::getInstance().createTests(pathToRun);
        for(auto& testCase: testCases) {
            std::cout << "Scheduling " << testCase->getPath() << std::endl;
            futures.emplace_back(std::async(_policy, [testCase, this]() {
                        std::cout << "Running " << testCase->getPath() << std::endl;
                        if(!testCase->doTest()) addFailure(testCase->getPath());
                    }));
            _numTestsRun++;
        }
    }

    for(auto& f: futures) f.wait();
    std::cout << std::endl;
               
    for(auto failure: _failures) {
        std::cout << "Test " << failure << " failed." << std::endl;        
    }

    return getElapsedSeconds(clock, start);
}

#include "test_library.hpp"
#include <iostream>
#include <tuple>
#include <boost/program_options.hpp>


namespace options = boost::program_options;


static options::options_description getOptionsDesc() {
    options::options_description desc("Usage: test <options> testcase1 testcase2 ...\n"
                                      "(each must either be a full testcase path or end with '/'");
    desc.add_options()
        ("help,h", "produce help message")
        ("show,s", "show avaiable test cases");
    return desc;
}

static options::variables_map getOptVars(int argc, char* argv[], const options::options_description& desc) {
    options::variables_map vars;
    options::store(options::parse_command_line(argc, argv, desc), vars);
    options::notify(vars);
    return vars;
}

static void printPaths() {
    std::cout << "Test cases:\n\n";
    for(const auto& path: TestSuite::getInstance().getPaths()) {
        std::cout << path << std::endl;
    }
    std::cout << std::endl;
}

static const int CARRY_ON = -1;
static int handleOptions(int argc, char* argv[]) {
    const auto desc = getOptionsDesc();
    try {
        const auto vars = getOptVars(argc, argv, desc);
        if(vars.count("help")) {
            std::cout << desc;
            return 0;
        }
        if(vars.count("show")) {
            printPaths();
            return 0;
        }
    } catch(options::error&) {
        std::cout << "Error parsing options" << std::endl;
        std::cout << desc;
        return 1;
    }
    return CARRY_ON;
}

static std::vector<std::string> getTestsToRun(int argc, char *argv[]) {
    std::vector<std::string> testsToRun;
    if(argc > 1) {
        for(int i = 1; i < argc; ++i) {
            testsToRun.emplace_back(argv[i]);
        }
    }
    return testsToRun;
}

int main(int argc, char* argv[]) {
    const int rc = handleOptions(argc, argv);
    if(rc != CARRY_ON) {
        return rc;
    }

    if(!TestSuite::getInstance().runTests(getTestsToRun(argc, argv))) {
        return 2;
    }

    if(!TestSuite::getInstance().getNumTestsRun()) {
        std::cout << "Did not run any tests!!!\n";
        return 3;
    }

    std::cout << TestSuite::getInstance().getNumTestsRun() << " test(s) run, " <<
                 TestSuite::getInstance().getNumFailures() << " failed.\n\n";

    if(TestSuite::getInstance().getNumFailures()) {
        std::cout << "Unit tests failed!\n\n";
        return 1; //oops
    }

    std::cout << "\nOK!\n\n";
}

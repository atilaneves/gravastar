#ifndef TEST_LIBRARY_HPP
#define TEST_LIBRARY_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>

class TestCase {
public:

    TestCase():_failed(false) { }
    virtual ~TestCase() { }
    bool doTest();

protected:

    template<typename T, typename U>
    bool verifyEqual(const T t, const U u) { return t == u ? true : fail(); }

    template<typename T, typename U>
    bool verifyNotEqual(const T t, const U u) { return t != u ? true : fail(); }

    template<typename T>
    bool verifyNull(const T* t) { return t == nullptr ? true : fail(); }

    template<typename T>
    bool verifyNotNull(const T* t) { return t != nullptr ? true : fail(); }

    template<typename C>
    bool verifyIn(const C& container, const typename C::value_type& obj) {
        return std::find(container.cbegin(), container.cend(), obj) != container.end() ? true : fail(); 
    }

    template<typename C>
    bool verifyNotIn(const C& container, const typename C::value_type& obj) {
        return std::find(container.cbegin(), container.cend(), obj) == container.cend() ? true : fail(); 
    }

    bool verifyTrue(bool condition);
    virtual void test() = 0;
    virtual void setup()    { }
    virtual void shutdown() { }

private:

    bool _failed;

    bool fail() { _failed = true; return false; }

};

typedef std::function<TestCase*()> TestCaseCreator;


class TestSuite {
public:

    static TestSuite& getInstance();
    bool registerTest(const std::string& name, const std::string& path, const TestCaseCreator& creator);
    void addFailure(const std::string& name);
    bool runTests(const std::vector<std::string>& testsToRun = std::vector<std::string>());
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


#define REGISTER_TEST(test, path) \
namespace { \
    TestCase* create_##test() { \
        return new test; \
    } \
    bool result_##test = TestSuite::getInstance().registerTest(#test, (path), create_##test); \
}


#define checkEqual(value, expected) \
    { \
        if(!verifyEqual((value), (expected))) \
            std::cout << __FILE__ << ":" << __LINE__ << \
                " Value " #value " is not the expected " #expected << std::endl; \
    }

#define checkNotEqual(value, expected)    \
    { \
        if(!verifyNotEqual((value), (expected))) \
            std::cout << __FILE__ << ":" << __LINE__ << \
                " Value " #value " is equal to the expected " #expected << std::endl; \
    }

#define checkNull(value) \
    { \
        if(!verifyNull((value)))                        \
            std::cout << __FILE__ << ":" << __LINE__ << \
                      " Value " #value " is not null " << std::endl; \
    }

#define checkNotNull(value) \
    { \
        if(!verifyNotNull((value))) \
            std::cout << __FILE__ << ":" << __LINE__ << \
                      " Value " #value " is null " << std::endl; \
    }

#define checkIn(container, value) \
    { \
        if(!verifyIn((container), (value))) \
            std::cout << __FILE__ << ":" << __LINE__ << \
                " Value " #value " not in container " << #container << std::endl; \
    }

#define checkNotIn(container, value) \
    { \
        if(!verifyNotIn((container), (value))) \
            std::cout << __FILE__ << ":" << __LINE__ << \
                " Value " #value " in container " << #container << std::endl; \
    }

#define checkTrue(value) \
    { \
        if(!verifyTrue((value))) \
            std::cout << __FILE__ << ":" << __LINE__ << \
                " Value " #value " is not true" << std::endl; \
    }


#endif

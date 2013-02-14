#ifndef TESTCASE_HPP_
#define TESTCASE_HPP_

#include <functional>
#include <algorithm>
#include <iostream>


class TestCase {
public:

    TestCase(const std::string& path):_failed(false), _path(path) { }
    virtual ~TestCase() { }
    const std::string& getPath() const { return _path; }
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
    const std::string _path;

    bool fail() { _failed = true; return false; }

};

typedef std::function<TestCase*()> TestCaseCreator;

#define REGISTER_TEST(test, path) \
namespace { \
    TestCase* create_##test() { \
        return new test((path));    \
    } \
    bool result_##test = TestCaseFactory::getInstance().registerTest((path), create_##test); \
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

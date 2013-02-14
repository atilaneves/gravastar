#include "test_library.hpp"
#include <string>
#include <list>

struct NumberTestCase: public TestCase {
    virtual void test() {
        checkTrue(true);
        checkEqual(1, 1);
        checkEqual(3.0, 3.0);
        checkNotEqual(2, 3);
        checkNotEqual(2.0, 2.1);
    }
};
REGISTER_TEST(NumberTestCase, "equals/numbers")


struct StringTestCase: public TestCase {
    virtual void test() {
        checkEqual(std::string("bar"), std::string("bar"));
        checkEqual("baz", "baz");
        checkNotEqual("foo", "bar");
    }
};
REGISTER_TEST(StringTestCase, "equals/strings")


struct TestObject {
    const int _int;
    const std::string _string;
    TestObject(int i, const std::string& s):_int(i), _string(s) { }
    bool operator==(const TestObject& rhs) const { return _int == rhs._int && _string == rhs._string; }
    bool operator!=(const TestObject& rhs) const { return !(*this == rhs); }
};

struct ObjectTestCase: public TestCase {
    virtual void test() {
        checkEqual(TestObject(1, "foo"), TestObject(1, "foo"));
        checkNotEqual(TestObject(1, "foo"), TestObject(2, "foo"));
        checkNotEqual(TestObject(1, "foo"), TestObject(1, "bar"));
    }
};
REGISTER_TEST(ObjectTestCase, "equals/objects")


struct NullTestCase: public TestCase {
    virtual void test() {
        //checkNull(nullptr);
        const TestObject* const nullObj = nullptr;
        checkNull(nullObj);
        const TestObject obj(7, "superman");
        checkNotNull(&obj);
    }
};
REGISTER_TEST(NullTestCase, "null")


struct ContainerTestCase: public TestCase {
    virtual void test() {
        std::vector<int> primes{3, 5, 7, 11, 13};
        checkIn(primes, 3);
        checkNotIn(primes, 2);
        checkIn(primes, 11);

        std::list<int> evens{2, 6, 8};
        checkIn(evens, 2);
        checkNotIn(evens, 5);

        std::map<int, double> intToDouble{{1, 2.0}, {2, 4.0}};
        checkIn(intToDouble, std::make_pair(1, 2.0));
        checkNotIn(intToDouble, std::make_pair(1, 3.0));

        std::vector<std::string> strings{"foo", "bar"};
        checkIn(strings, "foo");
        checkNotIn(strings, "baz");
        checkIn(strings, "bar");
    }
};
REGISTER_TEST(ContainerTestCase, "containers")


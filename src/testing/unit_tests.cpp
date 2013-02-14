#include "test_library.hpp"
#include <string>
#include <list>

SIMPLE_TEST(equals, Numbers,
    TEST(
        checkTrue(true);
        checkEqual(1, 1);
        checkEqual(3.0, 3.0);
        checkNotEqual(2, 3);
        checkNotEqual(2.0, 2.1);
    )
)


SIMPLE_TEST(equals, Strings,
    TEST(
        checkEqual(std::string("bar"), std::string("bar"));
        checkEqual("baz", "baz");
        checkNotEqual("foo", "bar");
    )
)

struct TestObject {
    const int _int;
    const std::string _string;
    TestObject(int i, const std::string& s):_int(i), _string(s) { }
    bool operator==(const TestObject& rhs) const { return _int == rhs._int && _string == rhs._string; }
    bool operator!=(const TestObject& rhs) const { return !(*this == rhs); }
};

SIMPLE_TEST(equals, Objects,
    TEST(
        checkEqual(TestObject(1, "foo"), TestObject(1, "foo"));
        checkNotEqual(TestObject(1, "foo"), TestObject(2, "foo"));
        checkNotEqual(TestObject(1, "foo"), TestObject(1, "bar"));
    )
)

SIMPLE_TEST(standalone, Null,
    TEST(
        const TestObject* const nullObj = nullptr;
        checkNull(nullObj);
        const TestObject obj(7, "superman");
        checkNotNull(&obj);
    )
)

SIMPLE_TEST(standalone, Containers,
    TEST(
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
    )
)

// namespace {
//     TestCase* create_BogusTest() {
//         return new ContainerTestCase;
//     }  
//     bool runLoads() {
//         for(int i = 0; i < 4000; ++i) {
//             TestCaseFactory::getInstance().registerTest("Bogus" + std::to_string(i), "bogus/" + std::to_string(i),
//                                                   create_BogusTest);
//         }
//         return true;
//     }
// bool resultBogus = runLoads();
// }

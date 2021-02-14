#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>

#define GREEN(x) ("\033[32m" + x + "\033[0m")
#define RED_SET "\033[0;31m"
#define KHAKI_SET "\033[38;2;240;230;140m"
#define RESET "\033[0m"
#define PINK_SET "\033[38:5:225m"
#define SPRING_GREEN_SET "\033[38;2;0;255;127m"
#define	WITH_BG "\033[48;2;0;250;154m\033[38;2;0;0;0m"

using namespace std;

template <class T, class U>
void AssertEqual(T const &t, U const &u, string const &hint) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << RED_SET << t << " != " << u
        << RESET << ". "
        << PINK_SET << hint << RESET;
        throw runtime_error(os.str());
    }
}

void Assert(bool b, string const &hint) {
    AssertEqual(b, true, hint);
}

template <class K, class V>
ostream &operator << (ostream &os, map<K, V> const &m) {
    os << "{";
    bool first = true;
    for (auto const &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T>
ostream &operator << (ostream &os, set<T> const &s) {
    os << "{";
    bool first = true;
    for (auto const &x : s) {
        os << ", ";
        first = false;
        os << x;
    }
    return os << "}";
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, string const &test_name) {
        try {
            func();
            // Use cerr to not mix tests output and program output
            cerr << test_name << ": "
                 << SPRING_GREEN_SET << "OK" << RESET << endl;
        } catch (runtime_error &ex) {
            ++fail_count;
            cerr << test_name << " fail: " << ex.what() << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

template<typename T>
T   sum(T a, T b) {
    return a + b;
}

void TestSum() {
    AssertEqual(sum(0, 0), 0, "Test 0 + 0");
    AssertEqual(sum(0, 1), 1, "Test 0 + 1");
    AssertEqual(sum(0, -1), -1, "Test 0 + -1");
    AssertEqual(sum(3, 2), 5, "Test 3 + 2");
    AssertEqual(sum(3, -2), 1, "Test 3 + -2");
    AssertEqual(sum(-5, -4), -9, "Test -5 + -4");
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestSum, "TestSum");
}

int main() {
    TestAll();

    return 0;
}

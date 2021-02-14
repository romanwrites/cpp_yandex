#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>

#define RED_SET "\033[0;31m"
#define RESET "\033[0m"
#define PINK_SET "\033[38:5:225m"
#define SPRING_GREEN_SET "\033[38;2;0;255;127m"

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

int GetDistinctRealRootCount(double a, double b, double c);


void TestConstant() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "c 1 has no real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0, "c -10 has no real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0, "c 189238910 has no real roots");
}

void TestLinearEquation() {
    AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1, "linear1");
    AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1, "linear2");
    AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1, "linear3");
}

void TestQuadraticEquation() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "quadratic1");
    AssertEqual(GetDistinctRealRootCount(1, 1, 0), 2, "quadratic2");
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "quadratic3");
    AssertEqual(GetDistinctRealRootCount(-1, 0, -1), 0, "quadratic4");
    AssertEqual(GetDistinctRealRootCount(1, 1, 1), 0, "quadratic5");
    AssertEqual(GetDistinctRealRootCount(1, 0, -1), 2, "quadratic6");
    AssertEqual(GetDistinctRealRootCount(-1, 0, 1), 2, "quadratic7");
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "quadratic8");
    AssertEqual(GetDistinctRealRootCount(1, 3, 2), 2, "quadratic9");
}


int main() {
    TestRunner tr;
    tr.RunTest(TestConstant, "TestConstant");
    tr.RunTest(TestLinearEquation, "TestLinearEquation");
    tr.RunTest(TestQuadraticEquation, "TestQuadraticEquation");

    return 0;
}

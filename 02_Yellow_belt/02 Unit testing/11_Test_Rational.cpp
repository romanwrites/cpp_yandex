#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <numeric>

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

class Rational {
public:
    Rational() {
        num = 0;
        denum = 1;
    }

    Rational(int numerator, int denominator) {
        int div = gcd(numerator, denominator);

        if (numerator < 0 && denominator < 0) {
            denum = abs(denominator) / div;
            num = abs(numerator) / div;
        } else if (denominator < 0) {
            denum = abs(denominator) / div;
            num = numerator / div;
            num = -num;
        } else {
            denum = denominator / div;
            num = numerator / div;
        }
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return denum;
    }

private:
    int num;
    int denum;
};

void TestBasicRationalFeatures() {
    int i = 0;
    {
        Rational defaultConstructed;
        AssertEqual(defaultConstructed.Numerator(), 0, "Basic " + to_string(++i));
        AssertEqual(defaultConstructed.Denominator(), 1, "Basic " + to_string(++i));
    }
    {
        Rational r(3, 10);
        AssertEqual(r.Numerator(), 3, "Basic " + to_string(++i));
        AssertEqual(r.Denominator(), 10, "Basic " + to_string(++i));
    }

    {
        Rational r(8, 12);
        AssertEqual(r.Numerator(), 2, "Basic " + to_string(++i));
        AssertEqual(r.Denominator(), 3, "Basic " + to_string(++i));
    }

    {
        Rational r(-4, 6);
        AssertEqual(r.Numerator(), -2, "Basic " + to_string(++i));
        AssertEqual(r.Denominator(), 3, "Basic " + to_string(++i));
    }

    {
        Rational r(4, -6);
        AssertEqual(r.Numerator(), -2, "Basic " + to_string(++i));
        AssertEqual(r.Denominator(), 3, "Basic " + to_string(++i));
    }

    {
        Rational r(0, 15);
        AssertEqual(r.Numerator(), 0, "Basic " + to_string(++i));
        AssertEqual(r.Denominator(), 1, "Basic " + to_string(++i));
    }
}


int main() {
    TestRunner tr;
    tr.RunTest(TestBasicRationalFeatures, "TestBasicRationalFeatures");

    return 0;
}

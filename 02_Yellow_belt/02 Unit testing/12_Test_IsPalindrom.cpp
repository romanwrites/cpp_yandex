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

bool	IsPalindrom(std::string const &str) {
    uint32_t half = str.length() / 2;
    for (uint32_t i = 0, j = str.length() - 1; i < half; i++, j--) {
        if (str[i] != str[j]) {
            return false;
        }
    }

    return true;
}

void TestEmpty() {
    AssertEqual(IsPalindrom(""), true, "Empty string");
}

void TestOneCharString() {
    AssertEqual(IsPalindrom("a"), true, "One char string 'a'");
    AssertEqual(IsPalindrom(","), true, "One char string ','");
    AssertEqual(IsPalindrom("Z"), true, "One char string 'Z'");
    AssertEqual(IsPalindrom(" "), true, "One char string ' '");
    AssertEqual(IsPalindrom("\n"), true, "One char string '\n'");
}

void TestTwoCharString() {
    AssertEqual(IsPalindrom("aa"), true, "Two char string");
    AssertEqual(IsPalindrom(",,"), true, "Two char string ','");
    AssertEqual(IsPalindrom("ZZ"), true, "Two char string 'Z'");
    AssertEqual(IsPalindrom("  "), true, "Two char string ' '");
    AssertEqual(IsPalindrom(" ,"), false, "Two char string \" ,\"");
    AssertEqual(IsPalindrom("a "), false, "Two char string \"a \"");
}

void TestCaseDifference() {
    AssertEqual(IsPalindrom("aAabBbBB"), false, "Test case difference");
}

void TestGeneral() {
    int i = 0;
    AssertEqual(IsPalindrom("madam"), true, "General " + to_string(++i));
    AssertEqual(IsPalindrom(" madam"), false, "General " + to_string(++i));
    AssertEqual(IsPalindrom("maddaam"), false, "General " + to_string(++i));
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), true, "General " + to_string(++i));
    AssertEqual(IsPalindrom("java"), false, "General " + to_string(++i));
    AssertEqual(IsPalindrom("javaj"), true, "General " + to_string(++i));
    AssertEqual(IsPalindrom("c++"), false, "General " + to_string(++i));
    AssertEqual(IsPalindrom("white etihw"), true, "General " + to_string(++i));
    AssertEqual(IsPalindrom("hite etiwh"), false, "General " + to_string(++i));
    AssertEqual(IsPalindrom("white etiw"), false, "General " + to_string(++i));
    AssertEqual(IsPalindrom("baobab"), false, "General " + to_string(++i));
    AssertEqual(IsPalindrom("     "), true, "General " + to_string(++i));
    AssertEqual(IsPalindrom("\t\t\t\t\t"), true, "General " + to_string(++i));
    AssertEqual(IsPalindrom("\t\t\t \t"), false, "General " + to_string(++i));
}

int main() {
    TestRunner tr;
    tr.RunTest(TestEmpty, "TestEmpty");
    tr.RunTest(TestGeneral, "TestGeneral");
    tr.RunTest(TestOneCharString, "TestOneCharString");
    tr.RunTest(TestTwoCharString, "TestTwoCharString");
    tr.RunTest(TestCaseDifference, "TestCaseDifference");
    tr.RunTest(TestCaseDifference, "TestCaseDifference");

    return 0;
}

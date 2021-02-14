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

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        if (m.find(year) == m.end()) {
            m[year]["first"] = first_name;
            m[year]["last"] = "no";
        } else {
            m[year]["first"] = first_name;
        }
    }
    void ChangeLastName(int year, const string& last_name) {
        if (m.find(year) == m.end()) {
            m[year]["first"] = "no";
            m[year]["last"] = last_name;
        } else {
            m[year]["last"] = last_name;
        }
    }
    string GetFullName(int year) {
        if (m.empty() || m.begin()->first > year) {
            return "Incognito";
        }
        auto it = m.begin();
        if (m.find(year) != m.end()) {
            it = m.find(year);
        } else {
            it = m.end();
            it--;
            while (it->first > year && it != m.begin()) {
                it--;
            }
        }
        stringstream ss;
        string first = getFirst(it);
        string last = getLast(it);
        if (first == "no") {
            ss << last << " with unknown first name";
        } else if (last == "no") {
            ss << first << " with unknown last name";
        } else {
            ss << first << " " << last;
        }
        return ss.str();
    }

private:
    map<int, map<string, string> >	m;

    template<typename T>
    string const &getFirst(T it) {
        if (it->second["first"] != "no") {
            return it->second["first"];
        }
        while (it->second["first"] == "no" && it != m.begin())
            it--;
        return it->second["first"];
    }

    template<typename T>
    string const &getLast(T it) {
        if (it->second["last"] != "no") {
            return it->second["last"];
        }
        while (it->second["last"] == "no" && it != m.begin())
            it--;
        return it->second["last"];
    }
};

void TestPreviousMain() {
    Person person;
    AssertEqual(person.GetFullName(2021), "Incognito", "Empty person GetFullName");

    person.ChangeFirstName(1965, "Polina");
    AssertEqual(person.GetFullName(1965), "Polina with unknown last name", "No last name 1");
    person.ChangeLastName(1967, "Sergeeva");
    AssertEqual(person.GetFullName(1965), "Polina with unknown last name", "No last name 2");
    AssertEqual(person.GetFullName(1967), "Polina Sergeeva", "Full name");

    person.ChangeFirstName(1970, "Appolinaria");
    AssertEqual(person.GetFullName(1969), "Polina Sergeeva", "Check name not changed before year 1970");
    AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva", "Check changed name");

    person.ChangeLastName(1968, "Volkova");
    AssertEqual(person.GetFullName(1969), "Polina Volkova", "Check last name changed 1");
    AssertEqual(person.GetFullName(1970), "Appolinaria Volkova", "Check last name changed 2");
}

void TestLastNameFirst() {
    Person person;

    person.ChangeLastName(1965, "Sergeeva");
    AssertEqual(person.GetFullName(1965), "Sergeeva with unknown first name", "No first name 1");
    AssertEqual(person.GetFullName(1964), "Incognito", "No name");
    person.ChangeFirstName(1966, "Polina");
    AssertEqual(person.GetFullName(1966), "Polina Sergeeva", "Full name");
}

int main() {
    TestRunner tr;
    tr.RunTest(TestPreviousMain, "TestPreviousMain");
    tr.RunTest(TestLastNameFirst, "TestLastNameFirst");

    return 0;
}

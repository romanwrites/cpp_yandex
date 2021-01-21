#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

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

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}

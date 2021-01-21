#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

template<typename T>
void PrintV(vector<T> const &v, string const &message) {
	cout << message << ":" << endl;
	for (auto const &i : v) {
		cout << i << " ";
	}
	cout << endl;
}

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		if (m.empty() || m.find(year) == m.end()) {
			m[year]["first"] = first_name;
			m[year]["last"] = "no";
		} else {
			m[year]["first"] = first_name;
		}
	}
	void ChangeLastName(int year, const string& last_name) {
		if (m.empty() || m.find(year) == m.end()) {
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

	string GetFullNameWithHistory(int year) {
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
		vector<string>	prevFirsts = getPrevFirsts(it, first);
		vector<string>	prevLasts = getPrevlasts(it, last);

		if (first == "no") {
			ss << last;
			if (!prevLasts.empty()) {
				ss << " (";
				for (int i = 0; i < prevLasts.size(); i++) {
					if (i == prevLasts.size() - 1) {
						ss << prevLasts[i];
					} else {
						ss << prevLasts[i] << ", ";
					}
				}
				ss << ") with unknown first name";
			} else {
				ss << " with unknown first name";
			}
		} else if (last == "no") {
			ss << first;
			if (!prevFirsts.empty()) {
				ss << " (";
				for (int i = 0; i < prevFirsts.size(); i++) {
					if (i == prevFirsts.size() - 1) {
						ss << prevFirsts[i];
					} else {
						ss << prevFirsts[i] << ", ";
					}
				}
				ss << ") with unknown last name";
			} else {
				ss << " with unknown last name";
			}
		} else {
			ss << first << " ";
			if (!prevFirsts.empty()) {
				ss << "(";
				for (int i = 0; i < prevFirsts.size(); i++) {
					if (i == prevFirsts.size() - 1) {
						ss << prevFirsts[i];
					} else {
						ss << prevFirsts[i] << ", ";
					}
				}
				ss << ") ";
			}
			ss << last;
			if (!prevLasts.empty()) {
				ss << " (";
				for (int i = 0; i < prevLasts.size(); i++) {
					if (i == prevLasts.size() - 1) {
						ss << prevLasts[i];
					} else {
						ss << prevLasts[i] << ", ";
					}
				}
				ss << ")";
			}
		}
		return ss.str();
	}
private:
	map<int, map<string, string> >	m;

	template<typename T>
	vector<string>	getPrevFirsts(T it, string const &first) {
		vector<string> v;
		while (it->second["first"] != first && it != m.begin())
			it--;
		if (it != m.begin())
			it--;
		while (it != m.begin()) {
			if (it->second["first"] != "no" && ((v.empty() && it->second["first"] != first) || (!v.empty() && v[v.size() - 1] != it->second["first"])))
				v.push_back(it->second["first"]);
			it--;
		}
		if (it == m.begin() && it->second["first"] != "no" && ((v.empty() && it->second["first"] != first) || (!v.empty() && v[v.size() - 1] != it->second["first"])))
			v.push_back(it->second["first"]);
		return v;
	}

	template<typename T>
	vector<string>	getPrevlasts(T it, string const &last) {
		vector<string> v;
		while (it->second["last"] != last && it != m.begin())
			it--;
		if (it != m.begin())
			it--;
		while (it != m.begin()) {
			if (it->second["last"] != "no" && ((v.empty() && it->second["last"] != last) || (!v.empty() && v[v.size() - 1] != it->second["last"])))
				v.push_back(it->second["last"]);
			it--;
		}
		if (it->second["last"] != "no" && ((v.empty() && it->second["last"] != last) || (!v.empty() && v[v.size() - 1] != it->second["last"])))
			v.push_back(it->second["last"]);
		return v;
	}

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
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;

	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) << endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;

	return 0;
}
//
//"Incognito"
//"Polina with unknown last name"
//"Polina Sergeeva"
//"Polina Sergeeva"
//"Appolinaria (Polina) Sergeeva"
//"Polina Volkova (Sergeeva)"
//"Appolinaria (Polina) Volkova (Sergeeva)"
//"Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)"
//"Pauline (Polina) with unknown last name"
//"Sergeeva with unknown first name"
//"Pauline (Polina) Sergeeva"
//"Pauline (Polina) Sergeeva (Ivanova, Sergeeva)"
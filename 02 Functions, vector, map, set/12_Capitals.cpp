#include <iostream>
#include <map>

using namespace std;

int 	main() {
	int n;
	cin >> n;
	map<string, string> countries;
	while (n > 0) {
		n--;
		string cmd;
		cin >> cmd;
		if (cmd == "CHANGE_CAPITAL") {
			string country, capital;
			cin >> country >> capital;
			auto it = countries.find(country);
			if (it == countries.end()) {
				countries[country] = capital;
				cout << "Introduce new country " << countries.find(country)->first
					<< " with capital " << countries.find(country)->second << endl;
			} else if (it->second == capital) {
				cout << "Country " << country << " hasn't changed its capital" << endl;
			} else {
				string oldCapital = countries[country];
				countries[country] = capital;
				cout << "Country " << country << " has changed its capital from " << oldCapital
					<< " to " << capital << endl;
			}
		} else if (cmd == "RENAME") {
			string oldCountry, newCountry;
			cin >> oldCountry >> newCountry;
			auto itOld = countries.find(oldCountry);
			auto itNew = countries.find(newCountry);
			if (itNew != countries.end() || itOld == countries.end() || oldCountry == newCountry) {
				cout << "Incorrect rename, skip" << endl;
			} else {
				swap(countries[newCountry], itOld->second);
				countries.erase(oldCountry);
				cout << "Country " << oldCountry << " with capital " << countries[newCountry]
					<< " has been renamed to " << newCountry << endl;
			}
		} else if (cmd == "ABOUT") {
			string country;
			cin >> country;
			auto it = countries.find(country);
			if (it == countries.end()) {
				cout << "Country " << country << " doesn't exist" << endl;
			} else {
				cout << "Country " << country << " has capital " << it->second << endl;
			}
		} else if (cmd == "DUMP") {
			if (countries.empty()) {
				cout << "There are no countries in the world" << endl;
			} else {
				for (const auto &i : countries) {
					cout << i.first << "/" << i.second << " ";
				}
				cout << endl;
			}
		}
	}
	return 0;
}

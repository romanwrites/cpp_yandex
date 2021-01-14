#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Bus {
	string bus;
	vector<string> stops;
};

bool 	isStopExists(const vector<Bus> &buses, const string &stop) {
	for (const auto &i : buses) {
		const auto &it = find(i.stops.begin(), i.stops.end(), stop);
		if (it != i.stops.end())
			return true;
	}
	return false;
}

void 	printBusesForStop(const vector<Bus> &buses, const string &stop) {
	if (isStopExists(buses, stop)) {
		vector<string>	busesForStop;

		for (const auto &i : buses) {
			for (const auto &j : i.stops) {
				if (j == stop) {
					busesForStop.push_back(i.bus);
				}
			}
		}

		for (int i = 0; i < busesForStop.size(); i++) {
			if (i + 1 == busesForStop.size()) {
				cout << busesForStop[i] << endl;
			} else {
				cout << busesForStop[i] << " ";
			}
		}
	} else {
		cout << "No stop" << endl;
	}
}

void	printInterchanges(const vector<Bus> &buses, const string &s, const string &bus) {
	int flag = 0;
	stringstream ss;
	for (int i = 0; i < buses.size(); i++) {
		if (find(buses[i].stops.begin(), buses[i].stops.end(), s) != buses[i].stops.end() \
			&& buses[i].bus != bus) {
			flag = 1;
			ss << buses[i].bus << " ";
		}
	}
	if (flag == 0) {
		cout << "no interchange" << endl;
	} else {
		string str = ss.str();
		str.pop_back();
		cout << str << endl;
	}
}

void 	printStops(const vector<Bus> &buses, const vector<string> &v, const string &bus) {
	for (const auto &i : v) {
		cout << "Stop " << i << ": ";
		printInterchanges(buses, i, bus);
	}
}

bool 	isBusExists(const vector<Bus> &buses, const string &bus) {
	for (const auto &i : buses) {
		if (i.bus == bus) {
			printStops(buses, i.stops, bus);
			return true;
		}
	}
	return false;
}

void 	printStopsOfBus(const vector<Bus> &buses, const string &bus) {

	if (!isBusExists(buses, bus)) {
		cout << "No bus" << endl;
	}
}

void 	printAllStops(const vector<string> &v, const string &bus) {
	cout << "Bus " << bus << ": ";
	for (int i = 0; i < v.size(); i++) {
		if (i + 1 == v.size()) {
			cout << v[i] << endl;
		} else {
			cout << v[i] << " ";
		}
	}
}

map<string, vector<string>>	busesToMap(const vector<Bus> &buses) {
	map<string, vector<string>>	m;
	for (const auto &i : buses) {
		m[i.bus] = i.stops;
	}
	return m;
}

int 	main() {
	int n;
	cin >> n;
	vector<Bus> buses;

	while (n > 0) {
		n--;
		string cmd;
		cin >> cmd;
		if (cmd == "NEW_BUS") {
			string stopTmp;
			int count;
			Bus newBus;
			cin >> newBus.bus >> count;
			while (count > 0) {
				count--;
				cin >> stopTmp;
				newBus.stops.push_back(stopTmp);
			}
			buses.push_back(newBus);
		} else if (cmd == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;
			printBusesForStop(buses, stop);
		} else if (cmd == "STOPS_FOR_BUS") {
			string bus;
			cin >> bus;
			printStopsOfBus(buses, bus);
		} else if (cmd == "ALL_BUSES") {
			if (!buses.empty()) {
				map<string, vector<string>> m = busesToMap(buses);
				for (const auto &i : m) {
					printAllStops(i.second, i.first);
				}
			} else {
				cout << "No buses" << endl;
			}
		}
	}
	return 0;
}

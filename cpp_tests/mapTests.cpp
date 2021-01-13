#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
void 	printMap(const T &m) {
	for (const auto& it : m) {
		cout << it.first << ": " << it.second << endl;
	}
}

int 	main() {
	cout << "----------- Test <string, string> map -----------" << endl;
	map<string, string>	langs;
	langs["Python"] = "Guido van Rossum";
	langs["Java"] = "James Gosling";
	langs["Java"] = "James Gosling"; // all keys are unique
	langs["C"] = "Brian Kernighan";
	langs["C++"] = "Bjarne Stroustrup";
	langs["JavaScript"] = "Brendan Eich"; // map is automatically sorted by key
	printMap(langs);

	cout << endl << "----------- Test <string, int> map -----------" << endl;
	map<string, int> m = {{"third", 3}, {"second", 2}, {"first", 1}}; // map is automatically sorted by key
	cout << "new map m:" << endl;
	printMap(m);
	cout << endl << "erase: " << m.find("second")->first << endl; // find() by the key, get value of the key
	m.erase("second");
	cout << "map m after erase:" << endl;
	printMap(m);

	cout << endl << "----------- Count quantity of values at vector with map -----------" << endl;
	vector<string> v = {"one", "one", "two", "three", "four", "two", "one"};
	map<string, int> counters;
	for (const auto &it : v) {
		if (counters.count(it) == 0) { // count returns how many times the key is found in the map
			counters[it] = 1;
		} else {
			counters[it]++;
		}
	}
	printMap(counters);
	return 0;
}

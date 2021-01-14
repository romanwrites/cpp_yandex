#include <iostream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int 	main() {
	int n;
	cin >> n;
	map<set<string>, int> m;

	while (n > 0) {
		n--;
		int count;
		cin >> count;
		set<string> stops;
		while (count > 0) {
			count--;
			string str;
			cin >> str;
			stops.insert(str);
		}
		if (m.find(stops) != m.end()) {
			cout << "Already exists for " << m[stops] << endl;
		} else {
			const uint32_t size = m.size() + 1;
			m[stops] = size;
			cout << "New bus " << size << endl;
		}
	}
	return 0;
}

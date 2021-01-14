#include <iostream>
#include <map>
#include <set>

using namespace std;

int 	main() {
	int n;
	cin >> n;
	map<string, set<string>> m;

	while (n > 0) {
		n--;
		string cmd;
		cin >> cmd;
		if (cmd == "ADD") {
			string a, b;
			cin >> a >> b;
			m[a].insert(b);
			m[b].insert(a);
		} else if (cmd == "COUNT") {
			string word;
			cin >> word;
			cout << m[word].size() << endl;
		} else if (cmd == "CHECK") {
			string a, b;
			cin >> a >> b;
			if (m.find(a) != m.end() && m[a].find(b) != m[a].end()) {
				cout << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
			}
		}
	}
	return 0;
}

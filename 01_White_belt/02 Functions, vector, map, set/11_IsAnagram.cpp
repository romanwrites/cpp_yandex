#include <iostream>
#include <map>

using namespace std;

map<char, int>	BuildCharCounters(const string &str) {
	map<char, int> m;
	for (const char &c : str) {
		m[c]++;
	}
	return m;
}

int main() {
	int n;
	cin >> n;
	while (n > 0) {
		n--;
		string s1, s2;
		cin >> s1 >> s2;
		map<char, int> a = BuildCharCounters(s1);
		map<char, int> b = BuildCharCounters(s2);
		if (a == b)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
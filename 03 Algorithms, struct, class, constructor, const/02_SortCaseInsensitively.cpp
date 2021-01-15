#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void Print(T const &c) {
	for (auto const &i : c) {
		cout << i << " ";
	}
}

string Tolower(string const &s) {
	string str = s;
	for (int i = 0; i < s.length(); i++) {
		str[i] = tolower(s[i]);
	}
	return str;
}

int main() {
	int n;
	cin >> n;
	vector<string>	v(n);
	for(auto &i : v) {
		cin >> i;
	}
	sort(v.begin(), v.end(), [](string const &a, string const &b) {
		return (Tolower(a) < Tolower(b));
	});
	Print(v);
	return 0;
}

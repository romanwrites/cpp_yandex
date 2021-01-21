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

int main() {
	int n;
	cin >> n;
	vector<string>	v(n);
	for(auto &i : v) {
		cin >> i;
	}
	sort(v.begin(), v.end(), [](string const &a, string const &b) {
		return lexicographical_compare(
				a.begin(), a.end(),
				b.begin(), b.end(),
				[](char ac, char ab) {
					return (tolower(ac) < tolower(ab));
		});
	});
	Print(v);
	return 0;
}

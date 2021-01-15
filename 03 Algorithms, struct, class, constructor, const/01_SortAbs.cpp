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
	vector<int>	v(n);
	for(auto &i : v) {
		cin >> i;
	}
	sort(v.begin(), v.end(), [](int a, int b) {
		return (abs(a) < abs(b));
	});
	Print(v);
	return 0;
}

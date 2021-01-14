#include <iostream>
#include <vector>
using namespace std;

int 	main() {
	int	n;
	cin >> n;
	vector<int>	days(n);
	int average = 0;
	for (auto &i : days) {
		cin >> i;
		average += i;
	}
	average /= days.size();
	vector<int> res;
	for (int i = 0; i < days.size(); i++) {
		if (days[i] > average) {
			res.push_back(i);
		}
	}
	cout << res.size() << endl;
	for (auto i : res) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}

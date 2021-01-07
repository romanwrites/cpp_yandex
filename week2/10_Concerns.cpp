#include <iostream>
#include <vector>

using namespace std;

struct Task {
	int idx;
	string task;
};

int 	main() {
	const vector<int> monthsNums = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int 	currentMonth = 0;
	vector<vector<string>> month(monthsNums[currentMonth]);
	int q;
	cin >> q;

	string cmd;
	Task t;

	for (int i = 0; i < q; i++) {
		cin >> cmd;
		if (cmd == "ADD") {
			cin >> t.idx >> t.task;
			month[t.idx - 1].push_back(t.task);
		} else if (cmd == "DUMP") {
			cin >> t.idx;
			cout << month[t.idx - 1].size() << " ";
			for (auto j : month[t.idx - 1]) {
				cout << j << " ";
			}
			cout << std::endl;
		} else if (cmd == "NEXT") {
			if (currentMonth + 1 <= 11) {
				currentMonth++;
			} else {
				currentMonth = 0;
			}
			if ((currentMonth > 0 && monthsNums[currentMonth] > monthsNums[currentMonth - 1]) ||
					(currentMonth == 0 && monthsNums[monthsNums.size() - 1] < currentMonth)) {
				month.resize(monthsNums[currentMonth]);
			} else {
				int diff;
				int startIdx = monthsNums[currentMonth] - 1;;
				if (currentMonth == 0) {
					diff = monthsNums[monthsNums.size() - 1] - monthsNums[0];
				} else {
					diff = monthsNums[currentMonth - 1] - monthsNums[currentMonth];
				}
				for (int j = 1; j <= diff; j++) {
					month[startIdx].insert(end(month[startIdx]), begin(month[startIdx + j]), end(month[startIdx + j]));
				}
				month.resize(monthsNums[currentMonth]);
			}
		}
	}
}

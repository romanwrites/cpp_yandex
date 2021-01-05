#include <iostream>
#include <vector>

using namespace std;

int 	getWorryCount(const vector<string> &queue) {
	int res = 0;

	for (const auto& i : queue) {
		if (i == "WORRY")
			res++;
	}
	return res;
}

int 	main() {
	int q;
	cin >> q;
	vector<string> queue(0);
	string cmd;
	int idx;
	int k;
	for (int i = 0; i < q; i++) {
		cin >> cmd;
		if (cmd == "COME") {
			cin >> k;
			if (k >= 0) {
				queue.insert(queue.end(), k, "QUIET");
			} else {
				k = -k;
				for (int j = 0; j < k; j++) {
					queue.pop_back();
				}
			}
		} else if (cmd == "WORRY") {
			cin >> idx;
			queue[idx] = "WORRY";
		} else if (cmd == "WORRY_COUNT") {
			cout << getWorryCount(queue) << endl;
		} else if (cmd == "QUIET") {
			cin >> idx;
			queue[idx] = "QUIET";
		}
	}
}

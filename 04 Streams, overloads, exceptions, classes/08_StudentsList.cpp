#include <iostream>
#include <vector>

using namespace std;

struct Student {
	string first;
	string last;
	int day;
	int month;
	int year;
};

int main() {
	int n;
	cin >> n;
	vector<Student> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i].first;
		cin >> v[i].last;
		cin >> v[i].day;
		cin >> v[i].month;
		cin >> v[i].year;
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		string cmd;
		int idx;
		cin >> cmd >> idx;
		if (idx < 1 || idx > v.size() || (cmd != "name" && cmd != "date"))
			cout << "bad request" << endl;
		else {
			idx--;
			if (cmd == "name") {
				cout << v[idx].first << " " << v[idx].last << endl;
			} else {
				cout << v[idx].day << "." << v[idx].month << "." << v[idx].year << endl;
			}
		}
	}
	return 0;
}

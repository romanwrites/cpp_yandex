#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SortedStrings {
public:
	SortedStrings() : _isSorted(false) {}
	~SortedStrings() {}

	void AddString(const string& s) {
		_v.push_back(s);
		_isSorted = false;
	}
	vector<string> GetSortedStrings() {
		if (!_isSorted) {
			sort(_v.begin(), _v.end());
			_isSorted = true;
		}
		return _v;
	}

private:
	vector<string>	_v;
	bool 			_isSorted;
};

void PrintSortedStrings(SortedStrings& strings) {
	for (const string& s : strings.GetSortedStrings()) {
		cout << s << " ";
	}
	cout << endl;
}

int main() {
	SortedStrings strings;

	strings.AddString("first");
	strings.AddString("third");
	strings.AddString("second");
	PrintSortedStrings(strings);

	strings.AddString("second");
	PrintSortedStrings(strings);

	return 0;
}

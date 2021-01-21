#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class ReversibleString {
public:
	ReversibleString() {}
	~ReversibleString() {}
	explicit ReversibleString(string const &str) : _str(str) {}

	void Reverse() {
		reverse(_str.begin(), _str.end());
	}

	string const &ToString() const {
		return _str;
	}

private:
	string _str;

};

int main() {
	ReversibleString s("live");
	s.Reverse();
	cout << s.ToString() << endl;

	s.Reverse();
	const ReversibleString& s_ref = s;
	string tmp = s_ref.ToString();
	cout << tmp << endl;

	ReversibleString empty;
	cout << '"' << empty.ToString() << '"' << endl;

	return 0;
}

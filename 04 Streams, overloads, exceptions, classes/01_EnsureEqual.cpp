#include <iostream>
#include <exception>

using namespace std;

void EnsureEqual(const string& left, const string& right) {

	if (left != right) {
		string	res = left + " != " + right;
		throw runtime_error(res);
	}
}

int main() {
	try {
		EnsureEqual("C++ White", "C++ White");
		EnsureEqual("C++ White", "C++ Yellow");
	} catch (runtime_error& e) {
		cout << e.what() << endl;
	}
	return 0;
}

// C++ White != C++ Yellow
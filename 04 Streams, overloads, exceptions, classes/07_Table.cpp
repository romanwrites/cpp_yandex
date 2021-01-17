#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	ifstream input("input.txt");
	int n, m;
	if (input) {
		input >> n >> m;
//		cout << left;
		while (n > 0) {
			n--;
			int j = m;
			while (j > 0) {
				j--;
				int val;
				input >> val;
				if (j > 0) {
					input.ignore(1);
					cout << setw(10) << val << " ";
				} else {
					cout << setw(10) << val;
				}
			}
			if (n > 0) {
				cout << endl;
			}
		}
	}

	return 0;
}

/*
input.txt
2 3
1,2,3
4,5,6
 */
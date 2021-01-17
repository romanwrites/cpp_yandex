#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	ifstream input("input.txt");
	double d;
	cout << fixed << setprecision(3);
	while (input >> d) {
		cout << d << endl;
	}
	return 0;
}

/*
 input.txt
 5
 0.34567
 10.4
 3.33353
 3.333
 3.3
 */
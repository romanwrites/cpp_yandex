#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream input("input.txt");
	string s;
	ofstream output("output.txt");
	while (getline(input, s)) {
		output << s << endl;
	}
	return 0;
}

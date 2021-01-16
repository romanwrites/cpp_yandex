#include <iostream>

using namespace std;

class Incognizable {
public:
	Incognizable() {}
	Incognizable(int x) : a(x) {}
	Incognizable(int x, int y) : a(x), b(y) {}

private:
	int a = 0;
	int b = 0;

};

int main() {
	Incognizable a;
	Incognizable b = {};
	Incognizable c = {0};
	Incognizable d = {0, 1};
	return 0;
}
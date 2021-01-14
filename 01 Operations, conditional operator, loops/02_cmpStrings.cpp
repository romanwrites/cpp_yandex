#include <iostream>

int		main() {
	std::string a, b, c, res;

	std::cin >> a >> b >> c;
	if (a <= b && a <= c) {
		res = a;
	} else if (b <= c) {
		res = b;
	} else {
		res = c;
	}
	std::cout << res<< std::endl;
	return 0;
}

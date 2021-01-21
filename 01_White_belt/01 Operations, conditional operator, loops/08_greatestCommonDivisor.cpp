#include <iostream>

int 	main() {
	int x, y, gcd;
	std::cin >> x >> y;

	while (true) {
		if (x > y) {
			if (x % y == 0) {
				gcd = y;
				break ;
			} else {
				x = x % y;
			}
		} else {
			if (y % x == 0) {
				gcd = x;
				break ;
			} else {
				y = y % x;
			}
		}
	}

	std::cout << gcd << std::endl;
}

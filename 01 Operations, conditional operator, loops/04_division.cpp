#include <iostream>
#include <cmath>

int 	main() {
	float	a, b;
	std::cin >> a >> b;

	if (b == 0) {
		std::cout << "Impossible" << std::endl;
	} else {
		std::cout << int(floorf(a / b)) << std::endl;
	}
}

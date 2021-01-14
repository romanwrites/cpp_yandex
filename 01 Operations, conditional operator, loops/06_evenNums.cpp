#include <iostream>
/*
 * Дано два целых числа A и B (A <= B, A >= 1, B <= 30000).
 * Выведите через пробел все чётные числа от A до B (включительно).
*/

int 	main() {
	int	a, b;
	std::cin >> a >> b;

	while (a <= b) {
		if (a % 2 == 0) {
			std::cout << a << " ";
		}
		a++;
	}

	return 0;
}

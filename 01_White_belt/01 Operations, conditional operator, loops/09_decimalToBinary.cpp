/* На вход дано целое положительное число N.
 * Выведите его в двоичной системе счисления без ведущих нулей. */

#include <iostream>
#include <vector>

int 	main() {
	int n, rem;
	std::vector<int> b;
	std::cin >> n;

	while (n > 0) {
		b.push_back(n % 2);
		n /= 2;
	}
	for (int i = b.size() - 1; i >= 0; i--) {
		std::cout << b[i];
	}
}

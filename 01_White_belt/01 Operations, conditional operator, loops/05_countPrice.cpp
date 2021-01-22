#include <iostream>
/*
 * Написать программу вычисления стоимости покупки товара с учётом скидки.
 * Если исходная стоимость товара больше A рублей, то на неё устанавливается скидка в X процентов.
 * Если исходная стоимость товара больше B рублей, то на неё устанавливается скидка в Y процентов.
 * На вход программе даны пять вещественных чисел: N, A, B, X, Y (A < B) -
 * где N - исходная стоимость товара. Выведите стоимость покупки товара с учётом скидки.
*/

int 	main() {
	float	n, a, b, x, y;
	std::cin >> n >> a >> b >> x >> y;

	if (n > b) {
		n -= n / 100 * y;
	} else if (n > a) {
		n -= n / 100 * x;
	}
	std::cout << n << std::endl;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

template<typename T>
void 	testVector(std::vector<T> &sequence) {
	std::cout << "Vector type is :\t" << typeid(sequence).name() << std::endl;
	std::cout << "Vector:\t\t\t\t";
	for (const auto& i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	sort(begin(sequence), end(sequence));
	std::cout << "Sorted vector:\t\t";
	for (const auto& i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl;
}

int		main() {
	std::vector<int> sequence = {1, 5, 2, 9, 4, 3, 7, 8, 6};
	testVector(sequence);

	std::vector<std::string> strSequence = {"hello", "world", "c++", "class", "vector"};
	testVector(strSequence);

	return 0;
}

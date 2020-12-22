#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

void 	testVector(std::vector<int> &sequence) {
	std::cout << "Vector type is :\t" << typeid(sequence).name() << std::endl;
	std::cout << "Vector:\t\t\t\t";
	for (auto i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	sort(begin(sequence), end(sequence));
	std::cout << "Sorted vector:\t\t";
	for (auto i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl << std::endl;
}

void 	testVector(std::vector<std::string> &sequence) {
	std::cout << "Vector type is :\t" << typeid(sequence).name() << std::endl;
	std::cout << "Vector:\t\t\t\t";
	for (auto i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	sort(begin(sequence), end(sequence));
	std::cout << "Sorted vector:\t\t";
	for (auto i : sequence) {
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
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

void 	testVector(std::vector<int> &sequence) {
	std::cout << "Vector type is :\t" << typeid(sequence).name() << std::endl;
	std::cout << "Vector:\t\t\t\t";
	for (auto i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	sort(begin(sequence), end(sequence));
	std::cout << "Sorted vector:\t\t";
	for (auto i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl << std::endl;
}

void 	testVector(std::vector<std::string> &sequence) {
	std::cout << "Vector type is :\t" << typeid(sequence).name() << std::endl;
	std::cout << "Vector:\t\t\t\t";
	for (auto i : sequence) {
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	sort(begin(sequence), end(sequence));
	std::cout << "Sorted vector:\t\t";
	for (auto i : sequence) {
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

#include <iostream>
#include <vector>

using namespace std;

struct Image {
	double quality;
	double freshness;
	double rating;
};

struct Params {
	double a;
	double b;
	double c;
};

class FunctionPart {
public:
	FunctionPart(char newOperation, double newValue) {
		operation = newOperation;
		value = newValue;
	}
	double Apply(double sourceValue) const {
		if (operation == '+') {
			return sourceValue + value;
		} else {
			return sourceValue - value;
		}
	}

	void Invert() {
		if (operation == '+') {
			operation = '-';
		} else {
			operation = '+';
		}
	}
private:
	char operation;
	double value;

};

class Function {
public:
	void	AddPart(char operation, double value) {
		parts.push_back({operation, value});
	}
	double	Apply(double value) const {
		for (FunctionPart const &part : parts) {
			value = part.Apply(value);
		}
		return value;
	}
	void 	Invert() {
		for (FunctionPart &part : parts) {
			part.Invert();
		}
		reverse(begin(parts), end(parts));
	}

private:
	vector<FunctionPart>	parts;
};

Function	MakeWeightFunction(Params const &params,
								Image const &image) {
	Function function;
	function.AddPart('-', image.freshness * params.a + params.b);
	function.AddPart('+', image.rating * params.c);
	return function;
}

double ComputeImageWeight(Params const &params,
						  Image const &image) {
	Function function = MakeWeightFunction(params, image);
	return function.Apply(image.quality);
}

double ComputeQualityByWeight(Params const &params,
							  Image const &image,
							  double weight) {
	Function function = MakeWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
}

int main() {
	Image	image = {10, 2, 6};
	Params	params = {4, 2, 6};
	cout << ComputeImageWeight(params, image) << endl;
	cout << ComputeQualityByWeight(params, image, 56) << endl;
	return 0;
}

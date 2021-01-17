#include <iostream>
#include <exception>
#include <numeric>
using namespace std;

class Rational {
public:
	Rational();
	Rational(int numerator, int denominator) {
		if (denominator == 0) {
			throw invalid_argument("denominator can't be 0");
		}
		if (numerator == 0) {
			num = 0;
			denum = 1;
			return ;
		}
		int div = gcd(numerator, denominator);

		if (numerator < 0 && denominator < 0) {
			denum = abs(denominator) / div;
			num = abs(numerator) / div;
		} else if (denominator < 0) {
			denum = abs(denominator) / div;
			num = numerator / div;
			num = -num;
		} else {
			denum = denominator / div;
			num = numerator / div;
		}
	}

	int Numerator() const {
		return num;
	}

	int Denominator() const {
		return denum;
	}

private:
	int num;
	int denum;

};

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("Numenator of rhs == 0");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}

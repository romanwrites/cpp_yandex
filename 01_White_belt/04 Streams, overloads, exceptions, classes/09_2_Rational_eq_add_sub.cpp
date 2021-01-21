#include <iostream>
#include <numeric>
using namespace std;

class Rational {
public:
	Rational() {
		num = 0;
		denum = 1;
	}

	Rational(int numerator, int denominator) {
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

	bool	operator==(Rational const &rhs) const {
		return num == rhs.num && denum == rhs.denum;
	}

	Rational	operator+(Rational const &rhs) const {
		int denomenator = denum * rhs.denum;
		int numenator = ((num * (denomenator / denum)) + (rhs.num * (denomenator / rhs.denum)));
		return Rational(numenator, denomenator);
	}

	Rational	operator-(Rational const &rhs) const {
		int denomenator = denum * rhs.denum;
		int numenator = ((num * (denomenator / denum)) - (rhs.num * (denomenator / rhs.denum)));
		return Rational(numenator, denomenator);
	}

private:
	int num;
	int denum;
};

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

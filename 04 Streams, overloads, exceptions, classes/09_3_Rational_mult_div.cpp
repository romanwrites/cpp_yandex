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

	Rational	operator*(Rational const &rhs) const {
		return Rational(num * rhs.num, denum * rhs.denum);
	}

	Rational	operator/(Rational const &rhs) const {
		return Rational(num * rhs.denum, denum * rhs.num);
	}

private:
	int num;
	int denum;
};

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}

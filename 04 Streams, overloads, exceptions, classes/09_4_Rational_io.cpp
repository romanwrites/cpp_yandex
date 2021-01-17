#include <iostream>
#include <numeric>
#include <sstream>
using namespace std;

class Rational {
public:
	Rational() {
		num = 0;
		denum = 1;
	}

	Rational(int numerator, int denominator) {
		RationalSetValue(numerator, denominator);
	}

	int Numerator() const {
		return num;
	}

	int Denominator() const {
		return denum;
	}

	void RationalSetValue(int numerator, int denominator) {
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

	bool	operator==(Rational const &rhs) const {
		return num == rhs.num && denum == rhs.denum;
	}

	Rational	operator+(Rational const &rhs) const {
		int denominator = denum * rhs.denum;
		int numerator = ((num * (denominator / denum)) + (rhs.num * (denominator / rhs.denum)));
		return Rational(numerator, denominator);
	}

	Rational	operator-(Rational const &rhs) const {
		int denominator = denum * rhs.denum;
		int numerator = ((num * (denominator / denum)) - (rhs.num * (denominator / rhs.denum)));
		return Rational(numerator, denominator);
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

ostream &operator<<(ostream &out, Rational const &obj) {
	out << obj.Numerator() << "/" << obj.Denominator();
	return out;
}

istream &operator>>(istream &in, Rational &obj) {
	if (in) {
		int numerator;
		int	denominator;
		in >> numerator;
		if (!in.fail() && !in.eof()) {
			char c;
			in >> c;
			if (!in.fail() && !in.eof() && c == '/') {
				in >> denominator;
				if (!in.fail())
					obj.RationalSetValue(numerator, denominator);
			}
		}
	}
	return in;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}

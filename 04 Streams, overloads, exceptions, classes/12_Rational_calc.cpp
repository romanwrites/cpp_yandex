#include <iostream>
#include <exception>
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
		if (denominator == 0) {
			throw invalid_argument("Invalid argument");
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

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

bool operator>(Rational const &lhs, Rational const &rhs) {
	int denominator = lhs.Denominator() * rhs.Denominator();
	return (lhs.Numerator() * (denominator / lhs.Denominator())) > (rhs.Numerator() * (denominator / rhs.Denominator()));
}

bool operator<(Rational const &lhs, Rational const &rhs) {
	int denominator = lhs.Denominator() * rhs.Denominator();
	return (lhs.Numerator() * (denominator / lhs.Denominator())) < (rhs.Numerator() * (denominator / rhs.Denominator()));
}

int main() {

	string str;
	getline(cin, str);
	stringstream ss;
	ss << str;

	string lhs, rhs;
	char operation;
	if (ss) {
		ss >> lhs;
		ss >> operation;
		ss >> rhs;
	}
    try {
		istringstream input(lhs + " " + rhs);
		Rational r1, r2, res;
		input >> r1 >> r2;
		if (operation == '+') {
			res = r1 + r2;
		} else if (operation == '-') {
			res = r1 - r2;
		} else if (operation == '*') {
			res = r1 * r2;
		} else {
			res = r1 / r2;
		}
		cout << res << endl;
	} catch (exception &ex) {
    	cout << ex.what() << endl;
    }
    return 0;
}

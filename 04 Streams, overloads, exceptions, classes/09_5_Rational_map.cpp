#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <numeric>
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

bool operator>(Rational const &lhs, Rational const &rhs) {
	int denominator = lhs.Denominator() * rhs.Denominator();
	return (lhs.Numerator() * (denominator / lhs.Denominator())) > (rhs.Numerator() * (denominator / rhs.Denominator()));
}

bool operator<(Rational const &lhs, Rational const &rhs) {
	int denominator = lhs.Denominator() * rhs.Denominator();
	return (lhs.Numerator() * (denominator / lhs.Denominator())) < (rhs.Numerator() * (denominator / rhs.Denominator()));
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

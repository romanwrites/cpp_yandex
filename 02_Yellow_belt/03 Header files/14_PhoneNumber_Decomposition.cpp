#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
    istringstream iss(international_number);
    char c;

    iss >> c;
    if (c != '+') {
        throw invalid_argument("No plus in front: " + international_number);
    }
    getline(iss, country_code_, '-');
    getline(iss, city_code_, '-');
    getline(iss, local_number_);

    if (country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument("Bad argument: " + international_number);
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

void TestPhoneNumber(string str) {
    try {
        PhoneNumber num(str);
        cerr << "Country code: " << num.GetCountryCode() << endl;
        cerr << "City code: " << num.GetCityCode() << endl;
        cerr << "Local number: " << num.GetLocalNumber() << endl;
        cerr << "International: " << num.GetInternationalNumber() << endl;
    } catch (invalid_argument &ex) {
        cerr << ex.what() << endl;
    }
    cerr << endl;
}

int main() {
    TestPhoneNumber("+7-495-111-22-33");
    TestPhoneNumber("+7-495-1112233");
    TestPhoneNumber("+323-22-460002");
    TestPhoneNumber("+1-2-coursera-cpp");
    TestPhoneNumber("1-2-333"); // incorrect
    TestPhoneNumber("+7-1233"); // incorrect
    return 0;
}

#include "phone_number.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
    if (international_number[0] != '+') {
        throw invalid_argument("No plus in front: " + international_number);
    }
    int i = 1;
    while (i < international_number.size() && international_number[i] != '-') {
        country_code_ += international_number[i];
        i++;
    }
    if (country_code_.empty() || international_number.size() == country_code_.size() + 1) {
        throw invalid_argument("Bad argument: " + international_number);
    }
    i++;
    while (i < international_number.size() && international_number[i] != '-') {
        city_code_ += international_number[i];
        i++;
    }
    if (city_code_.empty( )|| international_number.size() == city_code_.size() + country_code_.size() + 1) {
        throw invalid_argument("Bad argument: " + international_number);
    }
    i++;
    while (i < international_number.size()) {
        local_number_ += international_number[i];
        i++;
    }
    if (local_number_.empty()) {
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

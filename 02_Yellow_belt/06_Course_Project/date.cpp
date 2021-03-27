#include "date.h"
#include <iosfwd>
#include <sstream>

using namespace std;

// do need to throw an exception in case of bad args?
Date::Date(const int year, const int month, const int day)
    : year(year), month(month), day(day) {}

int Date::GetYear() const {
  return year;
}

int Date::GetMonth() const {
  return month;
}

int Date::GetDay() const {
  return day;
}

string Date::ToString() const {
  stringstream ss;

  ss << *this;
  return ss.str();
}

Date ParseDate(istream &is) {
  int year;
  int month;
  int day;

  is >> year;
  is.ignore(1);

  is >> month;
  is.ignore(1);

  is >> day;

  return Date(year, month, day);
}

std::ostream &operator<<(std::ostream &o, Date const &date) {
  o << std::setw(4) << std::setfill('0') << date.GetYear() << "-"
    << std::setw(2) << std::setfill('0') << date.GetMonth() << "-"
    << std::setw(2) << std::setfill('0') << date.GetDay();

  return o;
}

std::ostream &operator<<(std::ostream &o, Date &date) {
  o << std::setw(4) << std::setfill('0') << date.GetYear() << "-"
    << std::setw(2) << std::setfill('0') << date.GetMonth() << "-"
    << std::setw(2) << std::setfill('0') << date.GetDay();

  return o;
}

bool operator<(Date const &lhs, Date const &rhs) {
  return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>(Date const &lhs, Date const &rhs) {
  return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >
      std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator==(Date const &lhs, Date const &rhs) {
  return std::vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
      std::vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(Date const &lhs, Date const &rhs) {
  return !(lhs == rhs);
}

bool operator>=(Date const &lhs, Date const &rhs) {
  return !(lhs < rhs);
}

bool operator<=(Date const &lhs, Date const &rhs) {
  return !(lhs > rhs);
}
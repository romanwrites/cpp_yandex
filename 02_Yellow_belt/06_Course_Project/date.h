#pragma once
#include <string>
#include <iosfwd>
#include <iomanip>
#include <vector>

class Date {
 private:
  const int year;
  const int month;
  const int day;

 public:
  Date(int year, int month, int day);

  std::string ToString() const;

  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
};

Date ParseDate(std::istream &is);

std::ostream &operator<<(std::ostream &o, Date const &date);
std::ostream &operator<<(std::ostream &o, Date &date);

bool operator<(Date const &lhs, Date const &rhs);
bool operator>(Date const &lhs, Date const &rhs);
bool operator==(Date const &lhs, Date const &rhs);
bool operator!=(Date const &lhs, Date const &rhs);
bool operator>=(Date const &lhs, Date const &rhs);
bool operator<=(Date const &lhs, Date const &rhs);

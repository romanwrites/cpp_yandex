#pragma once

#include <ostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>

#define RED_SET "\033[0;31m"
#define KHAKI_SET "\033[38;2;240;230;140m"
#define RESET "\033[0m"
#define PINK_SET "\033[38:5:225m"
#define SPRING_GREEN_SET "\033[38;2;0;255;127m"

template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &s) {
  os << "[";
  bool first = true;
  for (auto const &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "]";
}

class TestRunner {
 public:
  template<class TestFunc>
  void RunTest(TestFunc func, std::string const &test_name) {
    try {
      func();
      // Use cerr to not mix tests output and program output
      std::cerr << KHAKI_SET << test_name << ": "
                << SPRING_GREEN_SET << "OK" << RESET << std::endl;
    } catch (std::runtime_error &ex) {
      ++fail_count;
      std::cerr << test_name << " fail: " << ex.what() << std::endl;
    }
  }

  ~TestRunner();

 private:
  int fail_count = 0;
};

template<class T, class U>
void AssertEqual(T const &t, U const &u, std::string const &hint) {
  if (t != u) {
    std::ostringstream os;
    os << "Assertion failed: " << RED_SET << t << " != " << u
       << RESET << ". "
       << PINK_SET << hint << RESET;
    throw std::runtime_error(os.str());
  }
}

void Assert(bool b, std::string const &hint);

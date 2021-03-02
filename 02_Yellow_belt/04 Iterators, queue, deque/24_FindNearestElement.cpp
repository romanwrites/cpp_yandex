#include <iostream>
#include <iterator>
#include <set>
using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
  auto it = numbers.lower_bound(border);

  if (it == numbers.begin()) {
    return numbers.begin();
  }
  if (it == numbers.end()) {
    return prev(it);
  }
  if (abs(border - *it) < abs(border - *prev(it))) {
    return it;
  }
  return prev(it);
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
       *FindNearestElement(numbers, 0) << " " <<
       *FindNearestElement(numbers, 3) << " " <<
       *FindNearestElement(numbers, 5) << " " <<
       *FindNearestElement(numbers, 6) << " " <<
       *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}

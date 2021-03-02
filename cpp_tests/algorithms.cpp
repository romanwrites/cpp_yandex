#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iterator>
#include <numeric>

using namespace std;

template<typename It>
void PrintRange(It range_begin, It range_end) {
  for (auto it = range_begin; it != range_end; ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

bool f(int i) {
  return i > 9;
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindSegment(
    RandomIt range_begin, RandomIt range_end, int left, int right) {
  return {lower_bound(range_begin, range_end, left),
          upper_bound(range_begin, range_end, right)};
}

int main() {
  vector<int> ve{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  auto its = FindSegment(ve.begin(), ve.end(), 9, 10);
  cout << *its.first << " " << *its.second << endl;
  cout << *next(its.first) << " " << *next(its.second) << endl;




  vector<string> langs = {
      "Python", "C++", "C", "Java", "C#", "Ruby", "JavaScript"
  };

  PrintRange(begin(langs), end(langs));
  PrintRange(begin(langs[0]), end(langs[0]));

  vector<string> c_langs(langs.size());
  copy_if(begin(langs), end(langs), begin(c_langs),
          [](const string &lang) {
            return lang[0] == 'C';
          });
  PrintRange(begin(c_langs), end(c_langs));

  auto result = find_if(begin(c_langs), end(c_langs),
                        [](string const &str) {
                          return str == "C#";
                        });

  *result = "Java";
  PrintRange(begin(c_langs), end(c_langs));

  set<string> one{"one", "two", "four", "five"};
  set<string> two{"one", "seven", "six", "five"};
  list<string> lst;
  set<string> in;

  set_intersection(begin(one), end(one), begin(two), end(two), back_inserter(lst));
  PrintRange(begin(lst), end(lst));
  cout << lst.size() << endl;

  set_intersection(begin(one), end(one), begin(two), end(two), inserter(in, end(in)));
  PrintRange(begin(in), end(in));
  cout << in.size() << endl;

//  const istream_iterator<string> start(cin);
//  const istream_iterator<string> end;
//  vector<string> strings(start, end);
//  vector<string> more_strings(start, end);
//  cout << "size: " << more_strings.size() << " " << more_strings[0]<< endl;
// more_strings состоит из одного элемента — strings[0]

//  const istream_iterator<string> start(cin);
//  auto start_copy = start;
//  ++start_copy;
//  cout << (start == start_copy) << endl;
//
//  set<int> s = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
//  vector<int> v;
//
//  remove_copy_if(begin(s), end(s), back_inserter(v), f);
//
//  PrintRange(begin(v), end(v));


  set<string> s = { "one","some string","two" };
  auto range = s.equal_range("some string");
  cout << (range.first == range.second) << endl;
  cout << *range.first << " " << *range.second << endl;

  cout << endl;



  return 0;

}

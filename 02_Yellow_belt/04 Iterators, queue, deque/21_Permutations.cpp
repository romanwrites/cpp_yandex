#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> v;
  for (int i = n; i > 0; --i) {
    v.push_back(i);
  }
  do {
    for (auto const &i : v) {
      cout << i << " ";
    }
    cout << endl;
  } while (prev_permutation(v.begin(), v.end()));
}

#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

template <typename It>
void MergeSort(It start, It finish) {
  // If range distance is lower than 2 — exit
  if (finish - start < 2) {
    return ;
  }
  // Create vector containing all alements of the range
  vector<typename It::value_type> elements(start, finish);

  // Split vector to two equal parts
  It halfBorder = elements.begin() + ((finish - start) / 2);

  // Call MergeSort with each part
  MergeSort(elements.begin(), halfBorder);
  MergeSort(halfBorder, elements.end());

  // Merge sorted halfs
  merge(elements.begin(), halfBorder, halfBorder, elements.end(), start);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

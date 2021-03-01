#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

// Split to 3 parts implementation
template <typename It>
void MergeSort(It start, It finish) {
  // If range distance is lower than 2 — exit
  if (finish - start < 2) {
    return ;
  }
  // Create vector containing all alements of the range
  vector<typename It::value_type> elements(start, finish);


  // Split vector to three parts
  It firstThirdBorder = elements.begin() + ((finish - start) / 3);
  It secondThirdBorder = elements.begin() + ((finish - start) * 2) / 3;

  // Call MergeSort with each part
  MergeSort(elements.begin(), firstThirdBorder);
  MergeSort(firstThirdBorder, secondThirdBorder);
  MergeSort(secondThirdBorder, elements.end());

  // Merge sorted halfs
  vector<typename It::value_type> firstAndSecondHalfs;
  merge(elements.begin(), firstThirdBorder, firstThirdBorder, secondThirdBorder, back_inserter(firstAndSecondHalfs));
  merge(firstAndSecondHalfs.begin(), firstAndSecondHalfs.end(), secondThirdBorder, elements.end(), start);
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

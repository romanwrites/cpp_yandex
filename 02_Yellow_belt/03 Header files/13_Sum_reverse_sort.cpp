#include <vector>
#include <iostream>
#include <algorithm>
#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    return string(s.rbegin(), s.rend());
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}

int main() {
    cout << Sum(10, 1) << endl;
    cout << Reverse("Zoom-zoom") << endl;
    vector<int> v = {5, 4, 3, 2, 1};
    Sort(v);
    for (auto const &i : v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
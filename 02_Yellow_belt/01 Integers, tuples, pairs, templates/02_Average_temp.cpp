#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    int64_t sum = 0;
    for (auto &i : v) {
        cin >> i;
        sum += i;
    }
    int average = sum / n;
    vector<int> aboveAverage;
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (v[i] > average)
            aboveAverage.push_back(i);
    }
    cout << aboveAverage.size() << endl;
    for (auto const &i : aboveAverage) {
        cout << i << " ";
    }

    return 0;
}

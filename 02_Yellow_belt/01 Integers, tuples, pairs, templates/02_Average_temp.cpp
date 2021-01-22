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
    int count = 0;
    for (auto const &i : v) {
        if (i > average)
            count++;
    }
    cout << count << endl;
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (v[i] > average)
            cout << i << " ";
    }

    return 0;
}
